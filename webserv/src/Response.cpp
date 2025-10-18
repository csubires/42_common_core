#include "../includes/Response.hpp"
#include "../includes/Request.hpp"
#include "../includes/utils.hpp"
#include <unistd.h>
#include <cstdlib>

Response::Response(const int client_fd, const Request& request, const ServerConfig& config, const std::vector<LocationConfig*>& locations)
	: client_fd(client_fd), request(request), config(config), locations(locations) {
	send_response.clear();
	send_header.clear();
	send_body.clear();
	status_code = 200;
	bytes_send = 0;
	counter = 0;
	response_header = new ResponseHeader();
}

Response::~Response() {
	delete response_header;
}

const char* Response::getResponse() {
    e_message log_type = SUCCESS;
    counter = 0;
    status_code = request.getStatusCode();
    LocationConfig* location = findLocation(request.getUri());

    std::vector<std::string> allowed_methods;
    if (location && !location->getMethods().empty()) {
        allowed_methods = location->getMethods();
    } else if (!config.getMethods().empty()) {
        allowed_methods = config.getMethods();
    }

    if (!allowed_methods.empty()) {
        std::string current_method = request.getMethod();
        bool method_allowed = false;
        for (size_t i = 0; i < allowed_methods.size(); ++i) {
            if (allowed_methods[i] == current_method) {
                method_allowed = true;
                break;
            }
        }
        if (!method_allowed) {
            status_code = 405;
            readContent(getPathStatusCode());
            response_header->setContentLength(send_body.size());
            send_header = response_header->getHeader(status_code);
            send_response = send_header;
            if (request.getMethod() != "HEAD")
                send_response.append(send_body);
            return send_response.data();
        }
    }

	if (location && !location->getRedirects().empty()) {
		std::vector<std::pair<std::string, std::string> > redirects = location->getRedirects();
		if (!redirects.empty()) {
			status_code = 301;
			response_header->setLocation(redirects[0].second);
			response_header->setContentLength(0);
			send_header = response_header->getHeader(status_code);
			send_response = send_header;
			return send_response.data();
		}
	}

	if (status_code == 200) {
		std::string resolvedPath = resolveFilePath(request.getUri());

		if (request.getMethod() == "GET" || request.getMethod() == "HEAD") {
			readContent(resolvedPath);
		} else if (request.getMethod() == "POST") {
			writeContent(resolvedPath, request.getBody());
		} else if (request.getMethod() == "DELETE") {
			if (location)
				deleteContent(location->getRoot());
			else {
				status_code = 404;
				readContent(getPathStatusCode());
			}
		} else {
			status_code = 405;
			readContent(getPathStatusCode());
		}
	} else {
		readContent(getPathStatusCode());
	}

	response_header->setContentLength(send_body.size());
	response_header->setContentType(request.getPath());
	send_header = response_header->getHeader(status_code);
	std::string cookie_headers = buildCookieHeaders();
	if (!cookie_headers.empty()) {
		size_t headerEndPos = send_header.find("\r\n\r\n");
		if (headerEndPos != std::string::npos) {

			send_header.insert(headerEndPos, cookie_headers);
			logger(STDOUT_FILENO, DEBUG, "Cookies added to response: " + cookie_headers);
		}
	}

	send_response.clear();
	send_response.append(send_header);
	if (request.getMethod() != "HEAD")
		send_response.append(send_body);

	if (status_code > 299 && request.getMethod() != "HEAD")
		log_type = ERROR;

	logger(STDOUT_FILENO, log_type, "Host: " + config.getHost() +
		" Response: " + request.getMethod() + " " + request.getPath() + " " +
		request.getHttpVersion() + " " + stringify(status_code) + " Size: " +
		stringify(send_body.size()) + "bytes");

	return send_response.data();
}

size_t Response::getSize() {
	return (send_response.size());
}

const std::string Response::getPathStatusCode() {
	std::string error_page_path;

	error_page_path.clear();
	switch (status_code) {
		case 201: error_page_path = ""; break;
		case 204: error_page_path = ""; break;
		case 301: error_page_path = ""; break;
		case 307: error_page_path = ""; break;
		case 400: error_page_path = ERROR_400_HTML; break;
		case 403: error_page_path = ERROR_403_HTML; break;
		case 404: error_page_path = ERROR_404_HTML; break;
		case 405: error_page_path = ERROR_405_HTML; break;
		case 413: error_page_path = ERROR_413_HTML; break;
		case 500: error_page_path = ERROR_500_HTML; break;
		case 502: error_page_path = ERROR_502_HTML; break;
		case 503: error_page_path = ERROR_503_HTML; break;
		case 504: error_page_path = ERROR_504_HTML; break;
		case 520: error_page_path = ""; break;
		default: error_page_path = ERROR_500_HTML;
	}

	std::vector<std::pair<std::string, int> > pairs = config.getErrorPages();
	for (std::vector<std::pair<std::string, int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it) {
		if (it->second == static_cast<int>(status_code)) { error_page_path = it->first;
			break;
		}
	}
	return (error_page_path);
}

void Response::readContent(const std::string &path) {
	if (++counter > 2) {
		status_code = 500;
		send_body.clear();
		send_body = MESSAGE_LOOP;
		return ;
	}

	if (status_code != 200 && status_code != 201 && status_code != 204) {
		std::string error_path = getPathStatusCode();
		if (pathIsFile(error_path)) {
			std::ifstream file(error_path.c_str());
			if (file.is_open()) {
				std::stringstream buffer;
				buffer << file.rdbuf();
				send_body = buffer.str();
				file.close();
			} else {
				send_body = ERROR_403_HTML;
			}
		} else {
			send_body = ERROR_403_HTML;
		}
		return ;
	}

	PathType result = checkPath(path);
	if (result == PATH_NOT_EXISTS) {
		status_code = 404;
		readContent(getPathStatusCode());
		return ;
	}
	std::string request_uri = request.getUri();
	LocationConfig* loc =  findLocation(request_uri);
	std::ifstream file;
	std::stringstream buffer;
	std::string index_file;

	if (result == PATH_IS_DIRECTORY && path[path.size()-1] != '/') {
		status_code = 301;
		response_header->setLocation(request.getUri() + "/");
		send_body.clear();
		return ;
	}

	if (shouldExecuteAsCGI(path)) {
		executeCGI(path);
		return ;
	}
	loc = findLocation(request.getUri());
	bool indexFound = false;
	const std::vector<std::string>& indexFiles = config.getIndexFiles();
	std::string error_path;

	switch (result) {
		case PATH_IS_FILE:
			file.open(path.c_str(), std::ifstream::in);
			if (!file.is_open()) {
				status_code = 403;
				readContent(getPathStatusCode());
				logger(STDOUT_FILENO, ERROR, "Cannot open file: " + path);
				return ;
			}
			buffer << file.rdbuf();
			send_body.clear();
			send_body = buffer.str();
			file.close();
			break;

		case PATH_IS_DIRECTORY:
			if (path[path.size()-1] != '/') {
				status_code = 301;
				response_header->setLocation(request.getUri() + "/");
				send_body.clear();
				return;
			}

			if (!config.getIndexFiles().empty()) {
				for (size_t i = 0; i < indexFiles.size(); ++i) {
					index_file = path + indexFiles[i];
					if (pathIsFile(index_file)) {
						readContent(index_file);
						indexFound = true;
						break;
					}
				}
				if (indexFound) break;
			}

			if (loc && loc->getAutoIndex()) {
				ListDirectory(path, request.getUri());
			} else {
				status_code = 403;
				error_path = getPathStatusCode();
				if (pathIsFile(error_path)) {
					std::ifstream file(error_path.c_str());
					if (file.is_open()) {
						std::stringstream buffer;
						buffer << file.rdbuf();
						send_body = buffer.str();
						file.close();
					}
				}
				if (send_body.empty()) {
					send_body = ERROR_403_HTML;
				}
			}
			break;

		case PATH_NO_PERMISSION:
			if (status_code != 403) {
				status_code = 403;
				readContent(getPathStatusCode());
			}
			break;

		case PATH_NOT_EXISTS:
			if (status_code != 404) {
				status_code = 404;
				logger(STDOUT_FILENO, ERROR, getPathStatusCode());
				readContent(getPathStatusCode());
			}
			break;

		case PATH_IS_OTHER:
			if (status_code != 400) {
				status_code = 400;
				readContent(getPathStatusCode());
			}
			break;

		case PATH_ERROR:
			if (status_code != 400) {
				status_code = 400;
				readContent(getPathStatusCode());
			}
			break;

		default:
			if (status_code != 404) {
				status_code = 404;
				readContent(getPathStatusCode());
			} else {
				status_code = 520;
				send_body.clear();
				return ;
			}
	}
}

void Response::writeContent(const std::string &path, std::string content)
{
	if (content.empty()) {
		status_code = 400;
		readContent(getPathStatusCode());
	}
	if (request.isMultipart() && !request.getUploadedFiles().empty()) {
		handleFileUpload();
		return ;
	}

	std::ofstream	file;
	if (pathIsFile(path))
	{
		file.open(path.c_str());
		file << content;
		file.close();
		status_code = 204;
		readContent(getPathStatusCode());
	} else {
		file.open(path.c_str(), std::ofstream::out | std::ofstream::trunc);
		if (file.is_open() == false)
		{
			status_code = 403;
			readContent(getPathStatusCode());
			return ;
		}
		file << content;
		file.close();
		status_code = 201;
		readContent(getPathStatusCode());
	}
}

void Response::handleFileUpload() {
    const std::map<std::string, std::string>& uploadedFiles = request.getUploadedFiles();
    size_t total_upload_size = 0;

    for (std::map<std::string, std::string>::const_iterator it = uploadedFiles.begin();
         it != uploadedFiles.end(); ++it) {
        total_upload_size += it->second.size();
    }

    LocationConfig* loc = findLocation(request.getUri());
    size_t max_upload_size = 0;

    if (loc && loc->getMaxBodySize() > 0)
        max_upload_size = loc->getMaxBodySize();
    else
        max_upload_size = config.getMaxBodySize();

    if (max_upload_size > 0 && total_upload_size > max_upload_size) {
        status_code = 413;
        readContent(getPathStatusCode());
        logger(STDOUT_FILENO, ERROR, "Upload size exceeds limit: " +
               stringify(total_upload_size) + " > " + stringify(max_upload_size));
        return;
    }
	std::string pathStr = request.getPath();
	std::string shortPath = pathStr.substr(pathStr.find_last_of('/'));
	loc = findLocation(shortPath + "/");
	std::string uploadDir;

	if (loc && !loc->getUploadPath().empty())
		uploadDir = loc->getUploadPath();
	else if (loc && !loc->getRoot().empty())
		uploadDir = loc->getRoot();
	else
		uploadDir = UPLOADS;

	if (!pathIsDirectory(uploadDir)) {
		errno = 0;
		if (mkdir(uploadDir.c_str(), 0755) != 0 && errno != EEXIST) {
			status_code = 500;
			readContent(getPathStatusCode());
			logger(STDOUT_FILENO, ERROR, "Cannot create upload directory: " + uploadDir);
			return ;
		}
	}

	std::string responseBody = "<html><body><h1>File Upload Results</h1><ul>";
	std::string jsonResponse = "[";
	bool success = false;
	bool firstFile = true;

	for (std::map<std::string, std::string>::const_iterator it = uploadedFiles.begin(); it != uploadedFiles.end(); ++it) {
		std::string filename = it->first;
		std::string fullPath = uploadDir + "/" + filename;

		std::ofstream file(fullPath.c_str(), std::ios::binary);
		if (file.is_open()) {
			file.write(it->second.c_str(), it->second.size());
			file.close();
			responseBody += "<li>File '" + it->first + "' uploaded successfully as: " + filename + "</li>";

			if (!firstFile) jsonResponse += ",";
			jsonResponse += "{\"original\":\"" + it->first + "\", \"filename\":\"" + filename + "\", \"path\":\"" + fullPath + "\"}";
			firstFile = false;

			success = true;
			logger(STDOUT_FILENO, SUCCESS, "File uploaded: " + fullPath + " size: " + stringify(it->second.size()));
		} else {
			responseBody += "<li>Failed to upload file: " + it->first + "</li>";
			logger(STDOUT_FILENO, ERROR, "Failed to write uploaded file: " + fullPath);
		}
	}

	responseBody += "</ul></body></html>";
	jsonResponse += "]";

	if (success) {
		status_code = 201;
		std::map<std::string, std::string> headers = request.getHeaders();

		if (headers.find("Accept") != headers.end() && headers["Accept"].find("application/json") != std::string::npos) {
			send_body = jsonResponse;
			response_header->setContentType("application/json");
		} else {
			send_body = responseBody;
		}
	} else {
		status_code = 500;
		readContent(getPathStatusCode());
	}
}

void Response::deleteContent(const std::string &path) {
	std::string targetPath = path;
	std::string uri = request.getUri();
	size_t queryPos = uri.find('?');

	if (queryPos != std::string::npos) {
		std::string queryString = uri.substr(queryPos + 1);
		logger(STDOUT_FILENO, SUCCESS, "Query string: " + queryString);
		std::string filename = "";
		size_t filenamePos = queryString.find("filename=");
		if (filenamePos != std::string::npos) {
			size_t valueStart = filenamePos + 9;
			size_t valueEnd = queryString.find('&', valueStart);
			if (valueEnd == std::string::npos)
				valueEnd = queryString.length();
			filename = queryString.substr(valueStart, valueEnd - valueStart);

			std::string decodedFilename = "";
			for (size_t i = 0; i < filename.length(); ++i) {
				if (filename[i] == '%' && i + 2 < filename.length()) {

					std::string hex = filename.substr(i + 1, 2);
					if (hex == "20") decodedFilename += ' ';
					else if (hex == "2E") decodedFilename += '.';
					else if (hex == "2D") decodedFilename += '-';
					else if (hex == "5F") decodedFilename += '_';
					else decodedFilename += filename[i];
					i += 2;
				} else if (filename[i] == '+') {
					decodedFilename += ' ';
				} else {
					decodedFilename += filename[i];
				}
			}
			filename = decodedFilename;
		}
		if (!filename.empty()) {
			std::string pathStr = request.getPath();
			std::string shortPath = pathStr.substr(pathStr.find('/'));
			LocationConfig* loc = findLocation(shortPath + "/");
			std::string uploadDir;
			if (loc && !loc->getUploadPath().empty())
				uploadDir = loc->getUploadPath();
			else if (loc && !loc->getRoot().empty())
				uploadDir = loc->getRoot();
			else
				uploadDir = "www/uploads";

			if (!uploadDir.empty()) {
				DIR* dir = opendir(uploadDir.c_str());
				if (dir) {
					struct dirent* entry;
					std::string foundFile = "";

					while ((entry = readdir(dir)) != NULL) {
						std::string entryName = entry->d_name;
						if (entryName.find(filename) == 0) {
							foundFile = uploadDir + "/" + entryName;
							break;
						}
					}
					closedir(dir);

					if (!foundFile.empty()) {
						targetPath = foundFile;
					} else {
						logger(STDOUT_FILENO, ERROR, "File " + filename + " not found in upload directory: " + uploadDir);
						status_code = 404;
						send_body.clear();
						return ;
					}
				} else {
					logger(STDOUT_FILENO, ERROR, "Cannot open upload directory: " + uploadDir);
					status_code = 404;
					send_body.clear();
					return ;
				}
			} else {
				logger(STDOUT_FILENO, ERROR, "Upload directory not configured");
				status_code = 500;
				send_body.clear();
				return ;
			}
		}
	}

	if (pathIsFile(targetPath)) {
		if (remove(targetPath.c_str()) == 0) {
			status_code = 204;
			send_body.clear();
			logger(STDOUT_FILENO, SUCCESS, "File deleted successfully: " + targetPath);
		} else {
			status_code = 403;
			send_body.clear();
			logger(STDOUT_FILENO, ERROR, "Failed to delete file (permission denied): " + targetPath);
		}
	} else {
		status_code = 404;
		send_body.clear();
		logger(STDOUT_FILENO, ERROR, "File not found: " + targetPath);
	}
}

void Response::ListDirectory(const std::string& path, const std::string& uri) {
	DIR* dir = opendir(path.c_str());
	if (!dir) {
		status_code = 404;
		readContent(getPathStatusCode());
		return ;
	}

	std::ostringstream listing;
	listing << "<html><head><title>Index of " << uri << "</title></head><body><h1>Index of " << uri << "</h1><hr><ul>";
	struct dirent* entry;
	if (uri != "/") {
		std::string tmp = uri;
		if (tmp.length() > 1 && tmp[tmp.length() - 1] == '/')
			tmp.erase(tmp.length() - 1);

		size_t pos = tmp.find_last_of('/');
		std::string parent_uri;
		if (pos == std::string::npos || pos == 0)
			parent_uri = "/";
		else
			parent_uri = tmp.substr(0, pos) + "/";

		listing << "<li><a href=\"" << parent_uri << "\">../</a></li>";
	}

	while ((entry = readdir(dir)) != NULL) {
		std::string name = entry->d_name;
		if (name != "." && name != "..") {

			std::string file_uri = uri;
			if (file_uri[file_uri.length() - 1] != '/')
				file_uri += "/";
			file_uri += name;

			std::string full_path = path;
			if (full_path[full_path.length() - 1] != '/')
				full_path += "/";
			full_path += name;

			std::string display_name = name;
			if (pathIsDirectory(full_path))
				display_name += "/";

			listing << "<li><a href=\"" << file_uri << "\">" << display_name << "</a></li>";
		}
	}
	listing << "</ul><hr></body></html>";
	closedir(dir);
	send_body.clear();
	send_body.append(listing.str());
	status_code = 200;
}

LocationConfig* Response::findLocation(const std::string& uri) {
	LocationConfig* best_match = NULL;

	for (std::vector<LocationConfig *>::const_iterator it = locations.begin(); it != locations.end(); ++it) {
		std::string location_path = (*it)->getLocationPath();
		if (location_path == "/") {
			if (!best_match) {
				best_match = *it;

			}
			continue;
		}
		if (uri == location_path ||
			(uri.length() > location_path.length() && uri.find(location_path + "/") == 0) ||
			(uri.length() >= location_path.length() &&
			uri.find(location_path) == 0 &&
			(uri.length() == location_path.length() ||
			uri[location_path.length()] == '/' || uri[location_path.length()] == '\0'))) {
			best_match = *it;
		}
	}
	return (best_match);
}

size_t Response::getStatusCode() const {
	return (status_code);
}

void Response::reset() {
	send_response.clear();
	send_header.clear();
	send_body.clear();
	status_code = 200;
	bytes_send = 0;
	counter = 0;
}

bool Response::shouldExecuteAsCGI(const std::string &path) {
    size_t dotPos = path.rfind('.');
    if (dotPos == std::string::npos)
        return false;
    std::string ext = path.substr(dotPos);
    if (ext != ".php" && ext != ".py" && ext != ".sh")
        return false;

    LocationConfig* loc = findLocation(request.getUri());
    if (loc && loc->getCgiEnabled()) {
        std::vector<std::pair<std::string, std::string> > cgiConfig = loc->getCgi();
        for (size_t i = 0; i < cgiConfig.size(); ++i) {
            if (cgiConfig[i].first == ext)
                return true;
        }
    }

    if (request.getUri().find("/cgi-bin/") == 0 || (loc && loc->getCgiEnabled()))
        return true;

    return false;
}

void Response::executeCGI(const std::string &path) {
	std::string absolutePath = path;
	if (path[0] != '/') {
		char* cwd = getcwd(NULL, 0);
		if (cwd) {
			absolutePath = std::string(cwd) + "/" + path;
			free(cwd);
		}
	}

	if (!pathIsFile(absolutePath)) {
		status_code = 404;
		send_body = "CGI script not found: " + absolutePath;
		return;
	}

	std::string uri = request.getUri();

	LocationConfig* loc = findLocation(uri.substr(uri.find_first_of("/"), uri.find_last_of("/") + 1));
	std::map<std::string, std::string> cgiEnv;
	std::vector<std::pair<std::string, std::string> > cgiData = loc->getCgi();


	for (size_t j = 0; j < cgiData.size(); j++) {
		logger(STDOUT_FILENO, ERROR, cgiData[j].first + "->" + cgiData[j].second);
	}

	Cgi cgi(absolutePath, cgiEnv, loc->getCgi());

	std::string queryString = "";
	size_t queryPos = request.getUri().find('?');
	if (queryPos != std::string::npos)
		queryString = request.getUri().substr(queryPos + 1);

	std::string contentType = "";
	std::string contentLengthStr = "0";
	std::map<std::string, std::string> headers = request.getHeaders();

	if (headers.find("Content-Type") != headers.end())
		contentType = headers["Content-Type"];
	if (headers.find("Content-Length") != headers.end())
		contentLengthStr = headers["Content-Length"];

	size_t contentLength = 0;
	if (!contentLengthStr.empty())
		contentLength = static_cast<size_t>(std::atoi(contentLengthStr.c_str()));


	std::string session_id = request.getSessionId();
	if (!session_id.empty()) {
		cgiEnv["HTTP_COOKIE"] = "SESSIONID=" + session_id;
	}

	cgi.setupEnvironment(
		request.getMethod(),
		request.getUri(),
		queryString,
		contentType,
		contentLength,
		config.getHost(),
		stringify(config.getPorts()[0]),
		headers
	);

	if (request.getMethod() == "POST" && !request.getBody().empty())
		cgi.setPostData(request.getBody());

	if (cgi.checkExtension() != 0) {
		status_code = 500;
		send_body = "CGI interpreter not available";
		return;
	}

	if (!cgi.execute()) {
		status_code = 500;
		std::string errorMsg = "CGI execution failed for: " + path;
		if (cgi.getStatus() != 0) {
			errorMsg += " (Exit status: " + stringify(cgi.getStatus()) + ")";
		}
		logger(STDOUT_FILENO, ERROR, errorMsg);
		send_body = errorMsg;
		return;
	}

	std::string cgiOutput = cgi.getOutput();
	std::string cgiHeaders = "";
	size_t headerEnd = cgiOutput.find("\r\n\r\n");
	if (headerEnd == std::string::npos) {

		headerEnd = cgiOutput.find("\n\n");
		if (headerEnd != std::string::npos) {
			cgiHeaders = cgiOutput.substr(0, headerEnd);
			send_body = cgiOutput.substr(headerEnd + 2);
		}
	} else {
		cgiHeaders = cgiOutput.substr(0, headerEnd);
		send_body = cgiOutput.substr(headerEnd + 4);
	}

	logger(STDOUT_FILENO, DEBUG, "CGI Headers length: " + stringify(cgiHeaders.length()));
	logger(STDOUT_FILENO, DEBUG, "CGI Body length: " + stringify(send_body.length()));
	std::istringstream headerStream(cgiHeaders);
	std::string line;

	while (std::getline(headerStream, line)) {
		if (!line.empty() && line[line.length()-1] == '\r')
			line = line.substr(0, line.length()-1);

		if (line.find("Set-Cookie:") == 0) {
			std::string cookieValue = line.substr(11);
			cookieValue = trim(cookieValue);
			size_t eqPos = cookieValue.find('=');
			if (eqPos != std::string::npos) {
				std::string cookieName = cookieValue.substr(0, eqPos);
				cookies[cookieName] = cookieValue;
				logger(STDOUT_FILENO, DEBUG, "CGI Cookie captured: " + cookieName + " = " + cookieValue);
			}
		} else if (line.find("Status:") == 0) {
			std::string statusStr = line.substr(7);
			statusStr = trim(statusStr);
			status_code = static_cast<size_t>(std::atoi(statusStr.c_str()));
		} else if (line.find("Content-Type:") == 0) {
			std::string contentType = line.substr(13);
			contentType = trim(contentType);
			response_header->setContentType(contentType);
		}
	}

	if (send_body.empty() && cgiHeaders.empty()) {
		status_code = 500;
		send_body = "CGI script produced no output";
	}
}

std::string Response::resolveFilePath(const std::string &uri) {
    LocationConfig* loc = findLocation(uri);
    std::string root;

    if (loc && !loc->getRoot().empty()) {
        root = loc->getRoot();
    } else {
        root = config.getRoot();
        if (root.empty()) {
            root = "www";
        }
    }
    root = normalizePath(root);
    if (root != "/" && !root.empty() && root[root.length()-1] == '/') {
        root = root.substr(0, root.length()-1);
    }

    std::string cleanUri = uri;
    size_t queryPos = uri.find('?');
    if (queryPos != std::string::npos) {
        cleanUri = uri.substr(0, queryPos);
    }
    cleanUri = normalizePath(cleanUri);
    if (loc) {
        const std::vector<std::string>& tryFiles = loc->getTryFiles();
        if (!tryFiles.empty()) {
            for (size_t i = 0; i < tryFiles.size(); ++i) {
                std::string candidate = tryFiles[i];

                if (!candidate.empty() && candidate[0] == '=') {
                    continue;
                }

                size_t pos = 0;
                std::string replaced;
                while ((pos = candidate.find("$uri", pos)) != std::string::npos) {
                    replaced += candidate.substr(0, pos);
                    replaced += cleanUri;
                    candidate = candidate.substr(pos + 4);
                    pos = 0;
                }
                replaced += candidate;
                candidate = replaced;
                std::string fullPath;
                if (!candidate.empty() && candidate[0] == '/') {

                    fullPath = normalizePath(root + candidate);
                } else {

                    fullPath = normalizePath(root + candidate);
                }
                logger(STDOUT_FILENO, DEBUG, "try_files candidate: " + fullPath);
                if (pathExists(fullPath) && (pathIsFile(fullPath) || pathIsDirectory(fullPath))) {
                    return fullPath;
                }
            }

        }
    }

    std::string filePath;
    if (cleanUri == "/") {
        filePath = root;
        if (!config.getIndexFiles().empty()) {
            filePath = normalizePath(filePath + "/" + config.getIndexFiles()[0]);
        } else {
            filePath = normalizePath(filePath + "/index.html");
        }
    } else {
        filePath = normalizePath(root + cleanUri);
    }
    logger(STDOUT_FILENO, DEBUG, "Resolved file path: " + filePath + " for URI: " + uri);
    return filePath;
}

void Response::removeCookie(const std::string& name) {

    setCookie(name, "", 0, "/");
}

void Response::setSessionCookie(const std::string& session_id) {
    setCookie("SESSIONID", session_id, 1800, "/");
}

std::string Response::buildCookieHeaders() {
	std::string cookie_headers;
	for (std::map<std::string, std::string>::const_iterator it = cookies.begin(); it != cookies.end(); ++it) {
		cookie_headers += "Set-Cookie: " + it->second + "\r\n";
		logger(STDOUT_FILENO, DEBUG, "Building cookie header: " + it->first);
	}
	return cookie_headers;
}

void Response::setCookie(const std::string& name, const std::string& value, time_t max_age, const std::string& path) {
	std::stringstream cookie;
	cookie << name << "=" << value;
	if (!path.empty())
		cookie << "; Path=" << path;
	if (max_age > 0)
		cookie << "; Max-Age=" << max_age;
	cookie << "; HttpOnly";
	cookies[name] = cookie.str();
	logger(STDOUT_FILENO, DEBUG, "Cookie set: " + name + " = " + value);
}
