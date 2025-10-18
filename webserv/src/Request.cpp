#include "../includes/Request.hpp"
#include "../includes/utils.hpp"

Request::Request(int client_fd, const ServerConfig& config) : config(config) {
    this->client_fd = client_fd;
	this->status_code = 200;
	this->method = "GET";
	this->valid_methods.push_back("GET");
	this->valid_methods.push_back("POST");
	this->valid_methods.push_back("DELETE");
	this->valid_methods.push_back("HEAD");
	this->valid_methods.push_back("UNKNOWN");
	this->path = "";
    this->uri = "http://localhost:8080";
	this->http_version = "";
	this->body = "";
    this->recv_data = "";
	this->isMultipartFormData = false;
	this->boundary = "";
	this->headers_parsed = false;
    this->content_length = 0;
    this->body_bytes_received = 0;
	this->filename = "";
}

Request::Request(const Request &other) : config(other.config) {
	client_fd = other.client_fd;
	parameters = other.parameters;
	headers = other.headers;
	method = other.method;
	path = other.path;
	http_version = other.http_version;
	body = other.body;
	filename = other.filename;
}

Request &Request::operator=(const Request &other) {
	if (this != &other) {
		client_fd = other.client_fd;
		parameters = other.parameters;
		headers = other.headers;
		method = other.method;
		path = other.path;
		http_version = other.http_version;
		body = other.body;
		filename = other.filename;
	}
	return *this;
}

Request::~Request() {}

void Request::setClientFd(int fd) {
	this->client_fd = fd;
}

int Request::getClientFd() const {
	return client_fd;
}

void Request::setMethod(const std::string &method) {
	this->method = method;
}

std::string Request::getMethod() const {
	return method;
}

void Request::setPath(const std::string &path) {
	this->path = path;
}

std::string Request::getPath() const {
	return path;
}

void Request::setHttpVersion(const std::string &http_version) {
	this->http_version = http_version;
}

std::string Request::getHttpVersion() const {
	return http_version;
}

void Request::setBody(const std::string &body) {
	this->body = body;
}

std::string Request::getBody() const {
	return body;
}

void Request::setStatusCode(ssize_t code) {
    this->status_code = code;
}

ssize_t Request::getStatusCode() const {
    return status_code;
}

void Request::setUri(const std::string &uri) {
    this->uri = uri;
}

std::string Request::getUri() const {
    return uri;
}

std::string Request::getFilename() const {
	return filename;
}

void Request::setFilename(const std::string &filename) {
	this->filename = filename;
}

void Request::parseParameters(const std::string &param_str) {
	size_t start = 0;
	size_t end = param_str.find('&');

	while (end != std::string::npos) {
		std::string param = param_str.substr(start, end - start);
		size_t eq_pos = param.find('=');
		if (eq_pos != std::string::npos) {
			std::string key = trim(param.substr(0, eq_pos));
			std::string value = trim(param.substr(eq_pos + 1));
			parameters[key] = value;
		}
		start = end + 1;
		end = param_str.find('&', start);
	}

	std::string param = param_str.substr(start);
	size_t eq_pos = param.find('=');
	if (eq_pos != std::string::npos) {
		std::string key = trim(param.substr(0, eq_pos));
		std::string value = trim(param.substr(eq_pos + 1));
		parameters[key] = value;
	}
}

bool Request::setSendData() {
    if (method == "UNKNOWN" || status_code != 200)
        return false;
    return true;
}

void Request::parseRecvData() {
    parameters.clear();
    headers.clear();
    body.clear();
    isMultipartFormData = false;
    boundary.clear();
    uploadedFiles.clear();

    if (recv_data.empty()) {
        status_code = 400;
        return;
    }

    std::istringstream request_stream(recv_data);
    std::string line;
    std::string method_local, uri_local, http_version_local;
    if (std::getline(request_stream, line)) {
        std::istringstream line_stream(line);
        if (!(line_stream >> method_local >> uri_local >> http_version_local)) {
            status_code = 400;
            return;
        }
    } else {
        status_code = 400;
        return;
    }

    bool valid_method = false;
    for (size_t i = 0; i < valid_methods.size(); ++i) {
        if (method_local == valid_methods[i]) {
            valid_method = true;
            break;
        }
    }
    if (!valid_method) {
        method = "UNKNOWN";
        status_code = 405;
        return;
    }

    size_t query_pos = uri_local.find('?');
	std::string clean_uri = (query_pos != std::string::npos) ? uri_local.substr(0, query_pos) : uri_local;
	clean_uri = normalizePath(clean_uri);

	if (query_pos != std::string::npos) {
		std::string param_str = uri_local.substr(query_pos + 1);
		parseParameters(param_str);
	}

	setMethod(method_local);
	setHttpVersion(http_version_local);
	setUri(clean_uri);
	if (query_pos != std::string::npos) {
		uri = uri_local;
	}

	std::string serverRoot = config.getRoot();
	if (serverRoot.empty())
		serverRoot = "www";

	serverRoot = normalizePath(serverRoot);

	if (!serverRoot.empty() && serverRoot[serverRoot.length()-1] == '/') {
		serverRoot = serverRoot.substr(0, serverRoot.length()-1);
	}

	if (clean_uri == "/") {
		path = serverRoot;
		if (!config.getIndexFiles().empty()) {
			path = normalizePath(path + "/" + config.getIndexFiles()[0]);
		} else {
			path = normalizePath(path + "/index.html");
		}
	} else {
		path = normalizePath(serverRoot + clean_uri);
	}
	path = normalizePath(path);

    while (std::getline(request_stream, line) && line != "\r") {
        size_t colon_pos = line.find(':');
        if (colon_pos != std::string::npos) {
            std::string header_name = trim(line.substr(0, colon_pos));
            std::string header_value = trim(line.substr(colon_pos + 1));
            headers[header_name] = header_value;
        }
    }

    std::string body_content;
    while (std::getline(request_stream, line)) {
        body_content += line + "\n";
    }
    if (!body_content.empty() && body_content[body_content.size() - 1] == '\n')
        body_content.erase(body_content.size() - 1);
    body = body_content;

	if (method == "POST")
		parseMultipartFormData();

	for (std::map<std::string, std::string>::iterator it = parameters.begin(); it != parameters.end(); ++it) {
		logger(STDOUT_FILENO, DEBUG, "  " + it->first + " = " + it->second);
	}
	logger(STDOUT_FILENO, DEBUG, "=== REQUEST PARSING ===");
	logger(STDOUT_FILENO, DEBUG, "Method: " + method);
	logger(STDOUT_FILENO, DEBUG, "URI: " + uri);
	logger(STDOUT_FILENO, DEBUG, "Path: " + path);
	logger(STDOUT_FILENO, DEBUG, "Content-Type: " + (headers.count("Content-Type") ? headers["Content-Type"] : "none"));
	logger(STDOUT_FILENO, DEBUG, "Content-Length: " + (headers.count("Content-Length") ? headers["Content-Length"] : "none"));
	logger(STDOUT_FILENO, DEBUG, "Body size: " + stringify(body.size()));
	logger(STDOUT_FILENO, DEBUG, "Headers:");
	for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); ++it) {
		logger(STDOUT_FILENO, DEBUG, "  " + it->first + ": " + it->second);
	}
    status_code = 200;

	if (headers.count("Transfer-Encoding") && headers["Transfer-Encoding"] == "chunked")
		body = decodeChunked(body_content);
	else
		body = body_content;

	parseCookies();
}

void Request::setRecvData(const std::string& src_recv_data, size_t bytes_read) {
	if (bytes_read <= 0 || bytes_read > BUFFER_RECV_SIZE) {
		logger(STDOUT_FILENO, ERROR, "Error reading from client or connection closed");
        status_code = 400;
		return;
	}
    if (!recv_data.empty()) {
        parseRecvData();
        recv_data.clear();
    }
	recv_data.append(src_recv_data);
    if (recv_data.find("\r\n\r\n") != std::string::npos)
        parseRecvData();
}

std::string Request::decodeChunked(const std::string &chunkedBody) {
	std::istringstream	stream(chunkedBody);
	std::string			decoded;
	std::string			line;

	while (std::getline(stream, line)) {
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		std::istringstream hexSize(line);
		size_t chunkSize = 0;
		hexSize >> std::hex >> chunkSize;

		if (!chunkSize)
			break;

		std::vector<char> buffer(chunkSize);
		stream.read(buffer.data(), chunkSize);
		decoded.append(buffer.begin(), buffer.end());
		stream.ignore(2);
	}
	return (decoded);
}

size_t Request::getBytesRecv() const {
	return (recv_data.size());
}

std::map<std::string, std::string> Request::getParameters() const {
    return parameters;
}

std::map<std::string, std::string> Request::getHeaders() const {
    return headers;
}

bool Request::isMultipart() const {
	return (isMultipartFormData);
}

std::string Request::getBoundary() const {
	return (boundary);
}

std::map<std::string, std::string> Request::getUploadedFiles() const {
	return (uploadedFiles);
}
void Request::parseMultipartFormData() {
	if (!headers.count("Content-Type")) {
		logger(STDOUT_FILENO, DEBUG, "No Content-Type header for multipart");
		return;
	}

	std::string contentType = headers["Content-Type"];
	size_t boundaryPos = contentType.find("boundary=");

	if (boundaryPos != std::string::npos) {
		isMultipartFormData = true;
		boundary = contentType.substr(boundaryPos + 9);
		if (!boundary.empty() && boundary[0] == '"' && boundary[boundary.length()-1] == '"')
			boundary = boundary.substr(1, boundary.length()-2);
		logger(STDOUT_FILENO, DEBUG, "Multipart detected. Boundary: '" + boundary + "'");
	}

	if (!isMultipartFormData || boundary.empty()) {
		logger(STDOUT_FILENO, DEBUG, "Not multipart or boundary empty");
		return;
	}

	std::string fullBoundary = "--" + boundary;
	logger(STDOUT_FILENO, DEBUG, "Full boundary: '" + fullBoundary + "'");
	logger(STDOUT_FILENO, DEBUG, "Body size: " + stringify(body.size()));
	size_t pos = 0;
	int partCount = 0;

	while ((pos = body.find(fullBoundary, pos)) != std::string::npos) {
		partCount++;
		logger(STDOUT_FILENO, DEBUG, "Found boundary at position: " + stringify(pos));

		size_t partStart = pos + fullBoundary.length();
		if (body.size() > partStart + 1 && body[partStart] == '\r' && body[partStart+1] == '\n')
			partStart += 2;
		else if (body.substr(partStart, 2) == "--") {
			logger(STDOUT_FILENO, DEBUG, "Found closing boundary");
			break;
		}

		size_t partEnd = body.find(fullBoundary, partStart);
		if (partEnd == std::string::npos) {
			logger(STDOUT_FILENO, ERROR, "No end boundary found for part " + stringify(partCount));
			break;
		}

		std::string part = body.substr(partStart, partEnd - partStart);
		logger(STDOUT_FILENO, DEBUG, "Part " + stringify(partCount) + " size: " + stringify(part.size()));

		size_t headerEnd = part.find("\r\n\r\n");
		if (headerEnd != std::string::npos) {
			std::string partHeaders = part.substr(0, headerEnd);
			std::string partBody = part.substr(headerEnd + 4);

			logger(STDOUT_FILENO, DEBUG, "Part headers size: " + stringify(partHeaders.size()));
			logger(STDOUT_FILENO, DEBUG, "Part body size: " + stringify(partBody.size()));

			size_t namePos = partHeaders.find("name=\"");
			size_t filenamePos = partHeaders.find("filename=\"");

			if (namePos != std::string::npos && filenamePos != std::string::npos) {
				size_t nameStart = namePos + 6;
				size_t nameEnd = partHeaders.find("\"", nameStart);
				std::string fieldName = partHeaders.substr(nameStart, nameEnd - nameStart);
				size_t filenameStart = filenamePos + 10;
				size_t filenameEnd = partHeaders.find("\"", filenameStart);
				std::string filename = partHeaders.substr(filenameStart, filenameEnd - filenameStart);
				logger(STDOUT_FILENO, DEBUG, "Field name: " + fieldName + ", Original filename: " + filename);
				size_t lastSlash = filename.find_last_of("/\\");
				if (lastSlash != std::string::npos)
					filename = filename.substr(lastSlash + 1);

				if (filename.empty()) {
					filename = fieldName;
				}

				while (filename.find("..") != std::string::npos)
					filename.replace(filename.find(".."), 2, "_");

				logger(STDOUT_FILENO, DEBUG, "Sanitized filename: " + filename);
				logger(STDOUT_FILENO, DEBUG, "File data size: " + stringify(partBody.size()));

				bool hasNullBytes = false;
				for (size_t i = 0; i < partBody.size() && i < 100; ++i) {
					if (partBody[i] == 0) {
						hasNullBytes = true;
						break;
					}
				}
				logger(STDOUT_FILENO, DEBUG, "File data contains null bytes: " + stringify(hasNullBytes));
				uploadedFiles[filename] = partBody;
				logger(STDOUT_FILENO, SUCCESS, "Uploaded file stored: " + filename + " size: " + stringify(partBody.size()));
			} else {
				logger(STDOUT_FILENO, WARNING, "No filename found in part headers");
			}
		} else {
			logger(STDOUT_FILENO, ERROR, "No header-body separator found in part");
		}
		pos = partEnd;
	}

}

bool Request::processReceivedData(const char* data, size_t bytes_read, bool& receiving_body, size_t& expected_body_size) {
    logger(STDOUT_FILENO, DEBUG, "processReceivedData: " + stringify(bytes_read) + " bytes, headers_parsed: " + stringify(headers_parsed));
   if (!headers_parsed) {
        size_t headers_end = recv_data.find("\r\n\r\n");
        if (headers_end != std::string::npos) {
            parseHeaders();
            headers_parsed = true;
        }
    }

    if (status_code == 413) {
        logger(STDOUT_FILENO, DEBUG, "Already detected oversized request, skipping data");
        return false;
    }

    size_t max_body_size = getMaxBodySize();
    size_t current_total_size = recv_data.size() + bytes_read;

    if (max_body_size > 0 && current_total_size > max_body_size) {
        logger(STDOUT_FILENO, ERROR, "Request body too large during reception: " +
               stringify(current_total_size) + " > " + stringify(max_body_size));
        status_code = 413;
        if (recv_data.size() < max_body_size) {
            size_t bytes_to_keep = max_body_size - recv_data.size();
            recv_data.append(data, bytes_to_keep);
        }
        return false;
    }

    recv_data.append(data, bytes_read);

    if (!headers_parsed) {
        size_t headers_end = recv_data.find("\r\n\r\n");
        if (headers_end != std::string::npos) {
            logger(STDOUT_FILENO, DEBUG, "Headers complete, parsing...");
            parseHeaders();
            headers_parsed = true;

            if (status_code == 413)
                return false;

			if (content_length > 0) {
				receiving_body = true;
				expected_body_size = content_length;
				logger(STDOUT_FILENO, DEBUG, "Expecting body of " + stringify(content_length) + " bytes");
				size_t headers_size = recv_data.find("\r\n\r\n") + 4;
				body_bytes_received = recv_data.size() - headers_size;

				if (body_bytes_received >= content_length) {
					logger(STDOUT_FILENO, INFO, "Body complete, parsing full request...");
					parseRecvData();
					receiving_body = false;
					return false;
				} else {
					logger(STDOUT_FILENO, INFO, "Body incomplete, continuing...");
					return true;
				}
			} else {
				parseRecvData();
				receiving_body = false;
				expected_body_size = 0;
				return false;
			}
		} else {
			logger(STDOUT_FILENO, INFO, "Headers incomplete, waiting for more data...");
			return true;
		}
	}

	if (receiving_body) {
		size_t headers_size = recv_data.find("\r\n\r\n") + 4;
		body_bytes_received = recv_data.size() - headers_size;
		logger(STDOUT_FILENO, INFO, "Body progress: " + stringify(body_bytes_received) + "/" + stringify(content_length) + " bytes");
		if (body_bytes_received >= content_length) {
			logger(STDOUT_FILENO, INFO, "Body complete, parsing full request...");
			parseRecvData();
			receiving_body = false;
			return false;
		} else {
			logger(STDOUT_FILENO, INFO, "Body incomplete, continuing...");
			return true;
		}
	}
	return false;
}

void Request::parseHeaders() {
    logger(STDOUT_FILENO, DEBUG, "=== PARSING HEADERS ===");
    size_t headers_end = recv_data.find("\r\n\r\n");
    std::string headers_str = recv_data.substr(0, headers_end);
    std::istringstream headers_stream(headers_str);
    std::string line;

    if (std::getline(headers_stream, line)) {
        std::istringstream line_stream(line);
        std::string method_local, uri_local, http_version_local;
        if (line_stream >> method_local >> uri_local >> http_version_local) {
            method = method_local;
            uri = uri_local;
            http_version = http_version_local;
            logger(STDOUT_FILENO, DEBUG, "Request line: " + method + " " + uri + " " + http_version);
        }
    }

    while (std::getline(headers_stream, line) && line != "\r") {
        size_t colon_pos = line.find(':');
        if (colon_pos != std::string::npos) {
            std::string header_name = trim(line.substr(0, colon_pos));
            std::string header_value = trim(line.substr(colon_pos + 1));
            headers[header_name] = header_value;
            logger(STDOUT_FILENO, DEBUG, "Header: " + header_name + ": " + header_value);

            if (header_name == "Content-Length") {
                content_length = atoi(header_value.c_str());
                logger(STDOUT_FILENO, DEBUG, "Found Content-Length: " + stringify(content_length));
                size_t max_body_size = getMaxBodySize();
                if (max_body_size > 0 && content_length > max_body_size) {
                    logger(STDOUT_FILENO, ERROR, "Content-Length exceeds limit at header parsing: " +
                           stringify(content_length) + " > " + stringify(max_body_size));
                    status_code = 413;
                    return;
                }
            }
        }
    }

    if (headers.count("Transfer-Encoding") && headers["Transfer-Encoding"] == "chunked") {
        logger(STDOUT_FILENO, DEBUG, "Chunked transfer encoding detected");
    }
}

bool Request::areHeadersComplete() const {
	return headers_parsed;
}

size_t Request::getRemainingBodySize() const {
	if (!headers_parsed || content_length == 0) return 0;
	return content_length - body_bytes_received;
}

size_t Request::getMaxBodySize() const {
    return config.getMaxBodySize();
}

void Request::reset() {
	status_code = 200;
	method = "GET";
	path = "";
	uri = "http://localhost:8080";
	http_version = "";
	body = "";
	recv_data = "";
	parameters.clear();
	headers.clear();
	isMultipartFormData = false;
	boundary = "";
	uploadedFiles.clear();
	headers_parsed = false;
	content_length = 0;
	body_bytes_received = 0;
}

void Request::parseCookies() {
    cookies.clear();
    std::map<std::string, std::string>::const_iterator it = headers.find("Cookie");
    if (it != headers.end()) {
        std::string cookie_header = it->second;
        std::istringstream stream(cookie_header);
        std::string pair;

        while (std::getline(stream, pair, ';')) {
            size_t pos = pair.find('=');
            if (pos != std::string::npos) {
                std::string name = trim(pair.substr(0, pos));
                std::string value = trim(pair.substr(pos + 1));
                cookies[name] = value;
            }
        }
    }
}

std::map<std::string, std::string> Request::getCookies() const {
    return cookies;
}

std::string Request::getCookie(const std::string& name) const {
    std::map<std::string, std::string>::const_iterator it = cookies.find(name);
    if (it != cookies.end()) {
        return it->second;
    }
    return "";
}

std::string Request::getSessionId() const {
    return getCookie("SESSIONID");
}
