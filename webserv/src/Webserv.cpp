#include "../includes/Webserv.hpp"
#include "../includes/utils.hpp"

Webserv* Webserv::signal_instance = NULL;

Webserv::Webserv(ConfigParsing &config) : config(config) {
	this->active = true;
	this->fds_sockets = std::map<int, ServerConfig*>();
	this->fds_clients = std::vector<int>();
	this->clients_state = std::map<int, ClientState>();
    this->session_cookie_name = "SESSIONID";
    this->session_timeout = 1800;
    cleanupExpiredSessions();
}

Webserv::~Webserv() {

	for (std::map<int, ClientState>::iterator it = clients_state.begin(); it != clients_state.end(); ++it) {
		if (it->second.request) {
			delete it->second.request;
			it->second.request = NULL;
		}
		if (it->second.response) {
			delete it->second.response;
			it->second.response = NULL;
		}
	}

	for (std::vector<int>::const_iterator it = fds_clients.begin(); it != fds_clients.end(); ++it)
		close(*it);

	for (std::map<int, ServerConfig*>::const_iterator it = fds_sockets.begin(); it != fds_sockets.end(); ++it)
		close((*it).first);
}

void Webserv::initializePorts() {
	int fd_socket;
	int opt = 1;
	int flags;

	const std::vector<ServerConfig*> servers = config.getServers();
	for (std::vector<ServerConfig*>::const_iterator it = servers.begin(); it != servers.end(); ++it) {

		const std::vector<int> ports = (*it)->getPorts();
		for (std::vector<int>::const_iterator it2 = ports.begin(); it2 != ports.end(); ++it2) {

			sockaddr_in server_addr;
			server_addr.sin_family = AF_INET;
			server_addr.sin_addr.s_addr = INADDR_ANY;
			server_addr.sin_port = htons(*it2);

			if ((fd_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
				throw std::runtime_error("The port " + stringify(ntohs(server_addr.sin_port)) + " could not be created.");

			if (setsockopt(fd_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
				throw std::runtime_error("Error setting socket parameters.");

			if (bind(fd_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
				throw std::runtime_error("Port assignment error " + stringify(ntohs(server_addr.sin_port)));

			if (listen(fd_socket, 10) < 0)
				throw std::runtime_error("Error listening on port " + stringify(ntohs(server_addr.sin_port)));

			flags = fcntl(fd_socket, F_GETFL, 0);
			if (flags == -1 || fcntl(fd_socket, F_SETFL, flags | O_NONBLOCK) == -1)
				throw std::runtime_error("Error setting socket non-blocking " + stringify(ntohs(server_addr.sin_port)));

			fds_sockets[fd_socket] = *it;
			logger(STDOUT_FILENO, INFO, (*it)->getHost() + " Listening at the port " + stringify(*it2));
		}
	}
}

int Webserv::initializeSelect(fd_set &read_fds, fd_set &write_fds) {
	int				max_fd = 0;
	int				client_fd;
	struct timeval	timeout = {1, 0};
	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);

	for (std::map<int, ServerConfig*>::const_iterator it = fds_sockets.begin(); it != fds_sockets.end(); ++it) {
		FD_SET(it->first, &read_fds);
		if (it->first > max_fd)
			max_fd = it->first;
	}

	for (size_t i = 0; i < fds_clients.size(); ++i) {
		client_fd = fds_clients[i];
		FD_SET(client_fd, &read_fds);
		if (clients_state[client_fd].ready_to_write)
			FD_SET(client_fd, &write_fds);
		if (client_fd > max_fd)
			max_fd = client_fd;
	}
	return (select(max_fd + 1, &read_fds, &write_fds, NULL, &timeout));
}

void Webserv::handleConnections(fd_set &read_fds) {
	int client_fd;

	for (std::map<int, ServerConfig*>::const_iterator it = fds_sockets.begin(); it != fds_sockets.end(); ++it) {

		if (FD_ISSET(it->first, &read_fds)) {
			struct sockaddr_in client_addr;
			socklen_t client_len = sizeof(client_addr);
			client_fd = accept(it->first, (struct sockaddr*)&client_addr, &client_len);

			if (client_fd < 0) {
				logger(STDOUT_FILENO, ERROR, "Error establishing incoming connection.");
				continue;
			}

			int flags = fcntl(client_fd, F_GETFL, 0);
			if (flags == -1 || fcntl(client_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
				logger(STDOUT_FILENO, ERROR, "Error setting client socket non-blocking");
				close(client_fd);
				continue;
			}

			const std::map<ServerConfig *, std::vector<LocationConfig*> >& map_loc = config.getLocations();
			std::map<ServerConfig *, std::vector<LocationConfig*> >::const_iterator loc = map_loc.find((*it).second);

		if (loc != map_loc.end()) {
			fds_clients.push_back(client_fd);
			clients_state[client_fd] = ClientState();
			clients_state[client_fd].request = new Request(client_fd, *it->second);
			clients_state[client_fd].response = new Response(client_fd, *clients_state[client_fd].request, *it->second, loc->second);
			clients_state[client_fd].last_activity = time(NULL);
			clients_state[client_fd].ready_to_read = true;
			clients_state[client_fd].ready_to_write = false;
			clients_state[client_fd].receiving_body = false;
			clients_state[client_fd].expected_body_size = 0;
			clients_state[client_fd].total_bytes_received = 0;
			clients_state[client_fd].headers_parsed = false;


			clients_state[client_fd].max_body_size = it->second->getMaxBodySize();
			if (clients_state[client_fd].max_body_size == 0) {

				clients_state[client_fd].max_body_size = MAX_BODY_SIZE;
			}
			clients_state[client_fd].request->reset();
			logger(STDOUT_FILENO, INFO, "New client connected: " + stringify(client_fd));
			} else {
				close(client_fd);
				logger(STDOUT_FILENO, ERROR, "New client not connected: " + stringify(client_fd));
			}
		}
	}
}

void Webserv::clientRequest(int client_fd, bool &close_connection) {
    ClientState& client_state = clients_state[client_fd];

    if (client_state.total_bytes_received == 0 && !client_state.headers_parsed) {
        char buffer[10];
        ssize_t peek_bytes = recv(client_fd, buffer, sizeof(buffer) - 1, MSG_PEEK);

        if (peek_bytes > 0 && static_cast<unsigned char>(buffer[0]) == 0x16) {
            logger(STDOUT_FILENO, INFO, "HTTPS connection refused - client: " + stringify(client_fd));
			std::string error_response = ERROR_400_HTML;
            send(client_fd, error_response.c_str(), error_response.size(), 0);
            close_connection = true;
            return;
        }
    }

    if (client_state.headers_parsed && client_state.max_body_size > 0) {
        if (client_state.total_bytes_received >= client_state.max_body_size) {
            logger(STDOUT_FILENO, ERROR, "Request already exceeded max body size: " +
                   stringify(client_state.total_bytes_received) + " >= " +
                   stringify(client_state.max_body_size));
            client_state.request->setStatusCode(413);
            client_state.ready_to_read = false;
            client_state.ready_to_write = true;
            return;
        }

        size_t remaining_quota = client_state.max_body_size - client_state.total_bytes_received;
        if (remaining_quota < BUFFER_RECV_SIZE) {
            std::vector<char> buffer(remaining_quota);
            ssize_t bytes_read = recv(client_fd, buffer.data(), remaining_quota, 0);

            if (bytes_read > 0) {
                client_state.total_bytes_received += bytes_read;

                if (client_state.total_bytes_received >= client_state.max_body_size) {
                    logger(STDOUT_FILENO, ERROR, "Request exceeded max body size during reception: " +
                           stringify(client_state.total_bytes_received) + " >= " +
                           stringify(client_state.max_body_size));
                    client_state.request->setStatusCode(413);
                }

                bool should_continue = client_state.request->processReceivedData(
                    buffer.data(), bytes_read,
                    client_state.receiving_body,
                    client_state.expected_body_size
                );

                if (!should_continue || client_state.request->getStatusCode() == 413) {
                    client_state.ready_to_read = false;
                    client_state.ready_to_write = true;
                }
            }
            return;
        }
    }

    std::vector<char> buffer(BUFFER_RECV_SIZE);
    ssize_t bytes_read = recv(client_fd, buffer.data(), buffer.size() - 1, 0);
	if (bytes_read < 0) {
		if (bytes_read == 0) {
			logger(STDOUT_FILENO, INFO, "Client " + stringify(client_fd) + " closed connection");
		}
		close_connection = true;
	} else if (bytes_read == 0) {
		close_connection = true;
	} else {
   		client_state.total_bytes_received += bytes_read;
        if (client_state.max_body_size > 0 &&
            client_state.total_bytes_received > client_state.max_body_size) {
            logger(STDOUT_FILENO, ERROR, "Request exceeded max body size: " +
                   stringify(client_state.total_bytes_received) + " > " +
                   stringify(client_state.max_body_size));
            client_state.request->setStatusCode(413);
        }

        bool should_continue_receiving = client_state.request->processReceivedData(
            buffer.data(), bytes_read,
            client_state.receiving_body,
            client_state.expected_body_size
        );

        if (!should_continue_receiving || client_state.request->getStatusCode() == 413) {
            client_state.ready_to_read = false;
            client_state.ready_to_write = true;
        }
        client_state.last_activity = time(NULL);
    }
}

void Webserv::clientResponse(int client_fd, bool &close_connection) {
    const char* response_data = clients_state[client_fd].response->getResponse();
    size_t response_size = clients_state[client_fd].response->getSize();
    ssize_t bytes_sent = send(client_fd, response_data, response_size, 0);

    if (bytes_sent < 0) {
        logger(STDOUT_FILENO, ERROR, "Send failed for client " + stringify(client_fd));
        close_connection = true;
    } else if ((size_t)bytes_sent < response_size) {
        logger(STDOUT_FILENO, WARNING, "Partial send: " + stringify(bytes_sent) + "/" + stringify(response_size) + " bytes");
        close_connection = true;
    } else {
        clients_state[client_fd].ready_to_write = false;
        std::map<std::string, std::string> headers = clients_state[client_fd].request->getHeaders();
        std::string connection_header = headers["Connection"];
        bool should_keep_alive = (connection_header == "keep-alive" || (connection_header.empty() && clients_state[client_fd].response->getStatusCode() < 400));
        if (should_keep_alive) {
            clients_state[client_fd].ready_to_read = true;
            clients_state[client_fd].ready_to_write = false;
            clients_state[client_fd].last_activity = time(NULL);
            clients_state[client_fd].request->reset();
            logger(STDOUT_FILENO, DEBUG, "Keeping connection alive for client " + stringify(client_fd));
        } else {
            close_connection = true;
            logger(STDOUT_FILENO, DEBUG, "Closing connection for client " + stringify(client_fd));
        }
    }
}

void Webserv::start() {
	int activity;
	int client_fd;
	bool close_connection;
	fd_set read_fds, write_fds;

	logger(STDOUT_FILENO, INFO, "Server ready to establish connections. PRESS CTRL + C TO EXIT");
	logger(STDOUT_FILENO, INFO, "Enable debug mode to see more information");

	while (active) {
		activity = initializeSelect(read_fds, write_fds);
		if (activity < 0) {
			if (errno == EINTR) {
				continue;
			} else {
				logger(STDERR_FILENO, ERROR, "Error in select()");
				throw std::runtime_error("Error in select()");
			}
		} else if (!activity) {
			continue;
		}

		handleConnections(read_fds);

		for (std::vector<int>::iterator it = fds_clients.begin(); it != fds_clients.end(); ) {
			client_fd = *it;
			close_connection = false;

			time_t current_time = time(NULL);
			if (current_time - clients_state[client_fd].last_activity > 30) {
				logger(STDOUT_FILENO, INFO, "Client timeout: " + stringify(client_fd));
				close_connection = true;
			}

			if (!close_connection && clients_state[client_fd].ready_to_read && FD_ISSET(client_fd, &read_fds)) {
				logger(STDOUT_FILENO, INFO, "Reading from client " + stringify(client_fd));
				clientRequest(client_fd, close_connection);
			}

			if (!close_connection && clients_state[client_fd].ready_to_write && FD_ISSET(client_fd, &write_fds)) {
				logger(STDOUT_FILENO, DEBUG, "Writing to client " + stringify(client_fd));
				clientResponse(client_fd, close_connection);
			}

			if (close_connection) {
				if (clients_state[client_fd].request) {
					delete clients_state[client_fd].request;
					clients_state[client_fd].request = NULL;
				}
				if (clients_state[client_fd].response) {
					delete clients_state[client_fd].response;
					clients_state[client_fd].response = NULL;
				}
				close(client_fd);
				clients_state.erase(client_fd);
				it = fds_clients.erase(it);
				logger(STDOUT_FILENO, INFO, "Client disconnected: " + stringify(client_fd));
			} else {
				++it;
			}
		}
	}
}

void Webserv::stop() {
	active = false;

	for (std::map<int, ClientState>::iterator it = clients_state.begin(); it != clients_state.end(); ++it) {
		if (it->second.request) {
			delete it->second.request;
			it->second.request = NULL;
		}
		if (it->second.response) {
			delete it->second.response;
			it->second.response = NULL;
		}
	}

	for (std::vector<int>::const_iterator it = fds_clients.begin(); it != fds_clients.end(); ++it)
		close(*it);

	fds_clients.clear();
	clients_state.clear();
}


std::string Webserv::generateSessionId() {
    std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string session_id;
    srand(time(NULL));

    for (int i = 0; i < 32; ++i) {
        session_id += chars[rand() % chars.length()];
    }
    return session_id;
}

Session* Webserv::getSession(const std::string& session_id) {
    if (session_id.empty()) return NULL;

    std::map<std::string, Session>::iterator it = sessions.find(session_id);
    if (it != sessions.end()) {

        if (time(NULL) - it->second.last_activity > session_timeout) {
            sessions.erase(it);
            return NULL;
        }
        it->second.last_activity = time(NULL);
        return &(it->second);
    }
    return NULL;
}

Session* Webserv::createSession() {
    std::string session_id = generateSessionId();
    Session new_session;
    new_session.id = session_id;
    new_session.last_activity = time(NULL);
    new_session.logged_in = false;
    sessions[session_id] = new_session;
    return &sessions[session_id];
}

bool Webserv::isValidSession(const std::string& session_id) {
    return getSession(session_id) != NULL;
}

void Webserv::cleanupExpiredSessions() {
    time_t current_time = time(NULL);
    std::map<std::string, Session>::iterator it = sessions.begin();

    while (it != sessions.end()) {
        if (current_time - it->second.last_activity > session_timeout) {
            sessions.erase(it++);
        } else {
            ++it;
        }
    }
}

std::string Webserv::parseCookies(const std::map<std::string, std::string>& headers) {
    std::map<std::string, std::string>::const_iterator it = headers.find("Cookie");
    if (it != headers.end()) {
        return it->second;
    }
    return "";
}

std::map<std::string, std::string> Webserv::parseCookieHeader(const std::string& cookie_header) {
    std::map<std::string, std::string> cookies;
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
    return cookies;
}

std::string Webserv::createCookieHeader(const std::string& name, const std::string& value, time_t max_age, const std::string& path, const std::string& domain) {
    std::stringstream cookie;
    cookie << name << "=" << value;
    cookie << "; Path=" << path;
    if (!domain.empty()) {
        cookie << "; Domain=" << domain;
    }
    cookie << "; Max-Age=" << max_age;
    cookie << "; HttpOnly";
    return cookie.str();
}
