#include "../includes/ConfigParsing.hpp"

ConfigParsing::ConfigParsing() {}

ConfigParsing::ConfigParsing(const ConfigParsing &other) {
    *this = other;
}

ConfigParsing &ConfigParsing::operator=(const ConfigParsing &other) {
	if (this != &other) {
		for (size_t i = 0; i < servers.size(); i++)
			delete servers[i];
		servers.clear();
		for (std::map<ServerConfig*, std::vector<LocationConfig*> >::iterator it = locations.begin();
			 it != locations.end(); ++it) {
			for (size_t j = 0; j < it->second.size(); j++)
				delete it->second[j];
		}
		locations.clear();
		for (size_t i = 0; i < other.servers.size(); i++)
			servers.push_back(new ServerConfig(*other.servers[i]));
	}
	return *this;
}

ConfigParsing::~ConfigParsing() {
    for (size_t i = 0; i < servers.size(); i++)
        delete servers[i];
    servers.clear();
	for (std::map<ServerConfig*, std::vector<LocationConfig*> >::iterator it = locations.begin();
		 it != locations.end(); ++it) {
		for (size_t j = 0; j < it->second.size(); j++)
			delete it->second[j];
		it->second.clear();
	}
	locations.clear();
}

std::vector<ServerConfig *> ConfigParsing::getServers() const {
    return servers;
}

const std::map<ServerConfig *, std::vector<LocationConfig*> >& ConfigParsing::getLocations() const {
    return locations;
}

void ConfigParsing::setConfigFile(const std::string &configFile) {
    this->configFile = configFile;
}

std::string ConfigParsing::getConfigFile() const {
    return this->configFile;
}

bool ConfigParsing::isFileReadable(const std::string &filePath) {
    std::ifstream file(filePath.c_str());
    struct stat s;
    if (stat(filePath.c_str(), &s) == 0 && S_ISDIR(s.st_mode))
        return false;
    if (filePath.size() < 5 || filePath.substr(filePath.size() - 5) != ".conf")
        return false;
    return file.good();
}

std::vector<std::string> ConfigParsing::tokenize(const std::string &filename, const std::string &delimiters) {
    std::ifstream file(filename.c_str());
    std::string content;
    if (file) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
    }
    std::vector<std::string> tokens;
    std::stringstream ss(content);
    std::string line;
    int brace = 0;
    while (std::getline(ss, line)) {
        size_t comment_pos = line.find('#');
        if (comment_pos != std::string::npos) {
            line = line.substr(0, comment_pos);
            line.erase(line.find_last_not_of(" \t") + 1);
        }
        if (line.find("{") != std::string::npos)
            brace++;
        if (line.find("}") != std::string::npos)
            brace--;
        if (!line.empty() && line[line.length() - 1] != ';' && line[line.length() - 1] != '{' && line[line.length() - 1] != '}') {
            logger(STDOUT_FILENO, ERROR, "Error: Missing semicolon or brace in line: " + line);
            continue;
        } else if (!line.empty() && line[line.length() - 1] == ';') {
            line = line.substr(0, line.length() - 1);
        }
        size_t pos = 0;
        while (pos < line.length()) {
            pos = line.find_first_not_of(delimiters, pos);
            if (pos == std::string::npos)
                break;
            size_t end = line.find_first_of(delimiters, pos);
            std::string token = (end == std::string::npos) ? line.substr(pos) : line.substr(pos, end - pos);
            if (!token.empty())
                tokens.push_back(token);
            pos = (end == std::string::npos) ? line.length() : end + 1;
        }
    }
    if (brace < 0)
        logger(STDOUT_FILENO, ERROR, "Error: Unmatched closing brace '}'");
    if (brace > 0)
        logger(STDOUT_FILENO, ERROR, "Error: Unmatched opening brace '{'");
    file.close();
    return tokens;
}

void ConfigParsing::parse(std::vector<std::string> &tokens) {
    size_t i = 0;
    while (i < tokens.size()) {
        if (tokens[i] == "server" && i + 1 < tokens.size() && tokens[i + 1] == "{") {
            ServerConfig* server = new ServerConfig();
            i += 2;
            while (i < tokens.size() && tokens[i] != "}") {
                if (tokens[i] == "listen") {
                    size_t j = i + 1;
                    while (j < tokens.size() && isdigit(tokens[j][0])) {
                        int port = atoi(tokens[j].c_str());
                        if (port <= 0 || port > 65535) {
                            logger(STDOUT_FILENO, ERROR, "Error: Invalid port number " + tokens[j]);
                            j++;
                            continue;
                        }
                        server->setPorts(port);
                        j++;
                    }
                    i = j;
                } else if (tokens[i] == "server_name") {
                    if (i + 1 < tokens.size()) {
                        server->setHost(tokens[i + 1]);
                        i += 2;
                    } else {
                        logger(STDOUT_FILENO, ERROR, "Error: Expected server name after 'server_name'");
                        i++;
                    }
                } else if (tokens[i] == "root") {
                    if (i + 1 < tokens.size()) {
                        server->setRoot(tokens[i + 1]);
                        i += 2;
                    } else {
                        logger(STDOUT_FILENO, ERROR, "Error: Expected path after 'root'");
                        i++;
                    }
                } else if (tokens[i] == "error_page") {
                    size_t j = i + 1;
                    std::vector<size_t> errorCodes;
                    std::string errorPage;
                    while (j < tokens.size()) {
                        if (tokens[j].find(".html") != std::string::npos) {
                            errorPage = tokens[j];
                            break;
                        } else {
                            size_t code = atoi(tokens[j].c_str());
                            if (code != 0)
                                errorCodes.push_back(code);
                        }
                        j++;
                    }
                    if (!errorPage.empty() && !errorCodes.empty()) {
                        for (size_t k = 0; k < errorCodes.size(); k++) {
                            server->addErrorPage(errorPage, errorCodes[k]);
                        }
                        i = j + 1;
                    } else {
                        logger(STDOUT_FILENO, ERROR, "Error: Invalid error_page directive");
                        i++;
                    }
				} else if (tokens[i] == "index") {
					size_t j = i + 1;
					while (j < tokens.size() && tokens[j] != "}" && tokens[j] != "location" &&
						tokens[j] != "listen" && tokens[j] != "server_name" &&
						tokens[j] != "root" && tokens[j] != "error_page" &&
						tokens[j] != "client_max_body_size" && tokens[j] != "method") {
						server->addIndexFile(tokens[j]);
						j++;
					}
					i = j;
				} else if (tokens[i] == "client_max_body_size") {
                    if (i + 1 < tokens.size()) {
                        size_t maxBodySize = static_cast<size_t>(atoi(tokens[i + 1].c_str()));
                        server->setMaxBodySize(maxBodySize);
                        i += 2;
                    } else {
                        logger(STDOUT_FILENO, ERROR, "Error: Expected size after 'client_max");
                        i++;
                    }
				} else if (tokens[i] == "method") {
                    std::vector<std::string> methods;
                    size_t j = i + 1;
                    while (j < tokens.size() && (tokens[j] == "GET" || tokens[j] == "POST" || tokens[j] == "DELETE" || tokens[j] == "HEAD")) {
                        methods.push_back(tokens[j]);
                        j++;
                    }
                    server->setMethods(methods);
                    i = j;
                } else if (tokens[i] == "location") {
                    LocationConfig* location = new LocationConfig(server);
                    if (i + 2 < tokens.size() && tokens[i + 2] == "{") {
                        location->setLocationPath(tokens[i + 1]);
                        i += 3; // Skip "location", path, and "{"
                        while (i < tokens.size() && tokens[i] != "}") {
                            if (tokens[i] == "autoindex") {
                                if (i + 1 < tokens.size()) {
                                    location->setAutoIndex(tokens[i + 1]);
                                    i += 2;
                                } else {
                                    logger(STDOUT_FILENO, ERROR, "Error: Expected 'on' or 'off' after 'autoindex'");
                                    i++;
                                }
							} else if (tokens[i] == "upload_path") {
									if (i + 1 < tokens.size()) {
										location->setUploadPath(tokens[i + 1]);
										i += 2;
									} else {
										logger(STDOUT_FILENO, ERROR, "Error: Expected path after 'upload_path'");
										i++;
									}

                            } else if (tokens[i] == "return") {
                                if (i + 2 < tokens.size() && isdigit(tokens[i + 1][0])
                                    && tokens[i + 1].size() == 3 && tokens[i + 1][0] == '3') {
                                    location->addRedirect(location->getLocationPath(), tokens[i + 2]);
                                    i += 3;
                                } else {
                                    logger(STDOUT_FILENO, ERROR, "Error: Expected return code and path after 'return'");
                                    i++;
                                }
                            } else if (tokens[i] == "try_files") {
                                i++;
                                while (i < tokens.size() && tokens[i] != "}") {
                                    location->addTryFile(tokens[i]);
                                    i++;
                                }
                            } else if (tokens[i] == "client_max_body_size") {
                                if (i + 1 < tokens.size()) {
                                    size_t maxBodySize = static_cast<size_t>(atoi(tokens[i + 1].c_str()));
                                    location->setMaxBodySize(maxBodySize);
                                    i += 2;
                                } else {
                                    logger(STDOUT_FILENO, ERROR, "Error: Expected size after 'client_max_body_size'");
                                    i++;
                                }
                            } else if (tokens[i] == "root") {
                                if (i + 1 < tokens.size()) {
                                    location->setRoot(tokens[i + 1]);
                                    i += 2;
                                } else {
                                    logger(STDOUT_FILENO, ERROR, "Error: Expected path after 'root'");
                                    i++;
                                }
                            } else if (tokens[i] == "method") {
                                std::vector<std::string> methods;
                                size_t j = i + 1;
                                while (j < tokens.size() && (tokens[j] == "GET" || tokens[j] == "POST" || tokens[j] == "DELETE" || tokens[j] == "HEAD")) {
                                    methods.push_back(tokens[j]);
                                    j++;
                                }
                                location->addMethods(methods);
                                i = j;
                            } else if (tokens[i] == "cgi_enabled") {
                                if (i + 1 < tokens.size()) {
                                    if (tokens[i + 1] == "on")
                                        location->setCgiEnabled(true);
                                    else if (tokens[i + 1] == "off")
                                        location->setCgiEnabled(false);
                                    else
                                        logger(STDOUT_FILENO, ERROR, "Error: Invalid value for cgi_enabled");
                                    i += 2;
                                } else {
                                    logger(STDOUT_FILENO, ERROR, "Error: Expected 'on' or 'off' after 'cgi_enabled'");
                                    i++;
                                }
                            } else if (tokens[i] == "cgi") {
                                if (i + 2 < tokens.size()) {
                                    location->addCgi(tokens[i + 1], tokens[i + 2]);
                                    i += 3;
                                } else {
                                    logger(STDOUT_FILENO, ERROR, "Error: Expected extension and interpreter after 'cgi'");
                                    i++;
                                }
                            } else if (tokens[i] == "include") {
                                if (i + 1 < tokens.size()) {
                                    location->addCgiInclude(tokens[i + 1]);
                                    i += 2;
                                } else {
                                    logger(STDOUT_FILENO, ERROR, "Error: Expected file path after 'include'");
                                    i++;
                                }
                            } else if (tokens[i] == "fastcgi_pass") {
                                if (i + 1 < tokens.size()) {
                                    location->setFastcgiPass(tokens[i + 1]);
                                    i += 2;
                                } else {
                                    logger(STDOUT_FILENO, ERROR, "Error: Expected address after 'fastcgi_pass'");
                                    i++;
                                }
                            } else if (tokens[i] == "fastcgi_index") {
                                if (i + 1 < tokens.size()) {
                                    location->setFastcgiIndex(tokens[i + 1]);
                                    i += 2;
                                } else {
                                    logger(STDOUT_FILENO, ERROR, "Error: Expected file name after 'fastcgi_index'");
                                    i++;
                                }
                            } else if (tokens[i] == "fastcgi_param") {
                                if (i + 2 < tokens.size()) {
                                    location->addFastcgiParam(tokens[i + 1], tokens[i + 2]);
                                    i += 3;
                                } else {
                                    logger(STDOUT_FILENO, ERROR, "Error: Expected parameter and value after 'fastcgi_param'");
                                    i++;
                                }
                            } else {
                                logger(STDOUT_FILENO, ERROR, "Unknown directive in location block: " + tokens[i]);
                                i++;
                            }
                        }
                        locations[server].push_back(location);
                        if (i < tokens.size() && tokens[i] == "}")
                            i++;
                    } else {
                        logger(STDOUT_FILENO, ERROR, "Error: Expected path and '{' after 'location'");
                        i++;
                    }
                } else {
                    i++;
                }
            }
            servers.push_back(server);
            if (i < tokens.size() && tokens[i] == "}")
                i++;
        } else {
            i++;
        }
    }
	if (DEBUG_MODE)
    	printConfig();
}

void ConfigParsing::printConfig() const {
    for (size_t i = 0; i < servers.size(); i++) {
        logger(STDOUT_FILENO, DEBUG, "Server " + stringify(i + 1) + ":");
        logger(STDOUT_FILENO, DEBUG, "  Host: " + servers[i]->getHost());
        logger(STDOUT_FILENO, DEBUG, "  Ports: ");
        std::vector<int> ports = servers[i]->getPorts();
        for (size_t j = 0; j < ports.size(); j++) {
            logger(STDOUT_FILENO, DEBUG, stringify(ports[j]));
        }
        logger(STDOUT_FILENO, DEBUG, "  Root: " + servers[i]->getRoot());
        logger(STDOUT_FILENO, DEBUG, "  Index: ");
        for (size_t j = 0; j < servers[i]->getIndexFiles().size(); j++) {
            logger(STDOUT_FILENO, DEBUG, servers[i]->getIndexFiles()[j]);
        }
        logger(STDOUT_FILENO, DEBUG, "  Error Pages:");
        for (size_t j = 0; j < servers[i]->getErrorPages().size(); j++) {
            logger(STDOUT_FILENO, DEBUG, "    " + stringify(servers[i]->getErrorPages()[j].second) +
                   "->" + servers[i]->getErrorPages()[j].first);
        }
        if (servers[i]->getMaxBodySize() > 0)
            logger(STDOUT_FILENO, DEBUG, "  Max Body Size: " + stringify(servers[i]->getMaxBodySize()) + " bytes");
        if (!servers[i]->getMethods().empty()) {
            logger(STDOUT_FILENO, DEBUG, "  Methods: ");
            std::vector<std::string> methods = servers[i]->getMethods();
            for (size_t j = 0; j < methods.size(); j++) {
                logger(STDOUT_FILENO, DEBUG, methods[j]);
            }
        }
        logger(STDOUT_FILENO, DEBUG, "  Locations: ");
        std::map<ServerConfig*, std::vector<LocationConfig*> >::const_iterator locIt = locations.find(servers[i]);
        if (locIt != locations.end()) {
            const std::vector<LocationConfig*>& locVec = locIt->second;
            for (size_t j = 0; j < locVec.size(); j++) {
                logger(STDOUT_FILENO, DEBUG, locVec[j]->getLocationPath());
            }
        }
    }

    size_t locCount = 1;
    for (std::map<ServerConfig*, std::vector<LocationConfig*> >::const_iterator it = locations.begin(); it != locations.end(); ++it) {
        for (size_t i = 0; i < it->second.size(); i++) {
            logger(STDOUT_FILENO, DEBUG, "Location " + stringify(locCount) + ": ");
            if (!it->second[i]->getLocationPath().empty())
                logger(STDOUT_FILENO, DEBUG, "  Path: " + it->second[i]->getLocationPath());
            logger(STDOUT_FILENO, DEBUG, "  AutoIndex: " + stringify(it->second[i]->getAutoIndex() ? "on" : "off"));
            if (!it->second[i]->getRedirects().empty()) {
                logger(STDOUT_FILENO, DEBUG, "  Redirects: ");
                std::vector<std::pair<std::string, std::string> > redirects = it->second[i]->getRedirects();
                for (size_t j = 0; j < redirects.size(); j++) {
                    logger(STDOUT_FILENO, DEBUG, redirects[j].first + "->" + redirects[j].second);
                }
            }
            if (!it->second[i]->getTryFiles().empty()) {
                logger(STDOUT_FILENO, DEBUG, "  Try Files: ");
                std::vector<std::string> tryFiles = it->second[i]->getTryFiles();
                for (size_t j = 0; j < tryFiles.size(); j++) {
                    logger(STDOUT_FILENO, DEBUG, tryFiles[j]);
                }
            }
            logger(STDOUT_FILENO, DEBUG, "  CGI Enabled: " + stringify(it->second[i]->getCgiEnabled() ? "on" : "off"));
            if (!it->second[i]->getCgi().empty()) {
                logger(STDOUT_FILENO, DEBUG, "  CGI: ");
                std::vector<std::pair<std::string, std::string> > cgi = it->second[i]->getCgi();
                for (size_t j = 0; j < cgi.size(); j++) {
                    logger(STDOUT_FILENO, DEBUG, cgi[j].first + "->" + cgi[j].second);
                }
            }
            if (!it->second[i]->getCgiIncludes().empty()) {
                logger(STDOUT_FILENO, DEBUG, "  CGI Includes: ");
                std::vector<std::string> cgiIncludes = it->second[i]->getCgiIncludes();
                for (size_t j = 0; j < cgiIncludes.size(); j++) {
                    logger(STDOUT_FILENO, DEBUG, cgiIncludes[j]);
                }
            }
            if (!it->second[i]->getFastcgiPass().empty())
                logger(STDOUT_FILENO, DEBUG, "  FastCGI Pass: " + it->second[i]->getFastcgiPass());
            if (!it->second[i]->getFastcgiIndex().empty())
                logger(STDOUT_FILENO, DEBUG, "  FastCGI Index: " + it->second[i]->getFastcgiIndex());
            if (!it->second[i]->getFastcgiParams().empty()) {
                logger(STDOUT_FILENO, DEBUG, "  FastCGI Params: ");
                std::vector<std::pair<std::string, std::string> > fastcgiParams = it->second[i]->getFastcgiParams();
                for (size_t j = 0; j < fastcgiParams.size(); j++) {
                    logger(STDOUT_FILENO, DEBUG, fastcgiParams[j].first + "=" + fastcgiParams[j].second);
                }
            }
            if (it->second[i]->getMaxBodySize() > 0)
                logger(STDOUT_FILENO, DEBUG, "  Max Body Size: " + stringify(it->second[i]->getMaxBodySize()) + " bytes");
            if (!it->second[i]->getMethods().empty()) {
                logger(STDOUT_FILENO, DEBUG, "  Methods: ");
                std::vector<std::string> methods = it->second[i]->getMethods();
                for (size_t j = 0; j < methods.size(); j++) {
                    logger(STDOUT_FILENO, DEBUG, methods[j]);
                }
            }
            if (!it->second[i]->getUploadPath().empty())
                logger(STDOUT_FILENO, DEBUG, "  Upload Path: " + it->second[i]->getUploadPath());
            if (!it->second[i]->getRoot().empty())
                logger(STDOUT_FILENO, DEBUG, "  Root: " + it->second[i]->getRoot());
            locCount++;
        }
    }
}
