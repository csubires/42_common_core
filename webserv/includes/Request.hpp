#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Webserv.hpp"
#include "ServerConfig.hpp"

class ServerConfig;

class Request {
	private:
		std::map<std::string, std::string>	parameters;
		std::map<std::string, std::string>	headers;
		std::vector<std::string>	valid_methods;
		std::string	method;
		std::string path;
		std::string	uri;
		std::string	http_version;
		std::string body;
		ssize_t		status_code;
		int			client_fd;
		std::string	recv_data;
		const ServerConfig& config;
		std::string filename;
		bool headers_parsed;
        size_t content_length;
        size_t body_bytes_received;
		bool isMultipartFormData;
		std::string boundary;
		std::map<std::string, std::string> uploadedFiles;
		std::map<std::string, std::string> cookies;

	public:
		Request(int client_fd, const ServerConfig& config);
		Request(const Request &other);
		Request &operator=(const Request &other);
		~Request();

		void parseParameters(const std::string &param_str);
		void setRecvData(const std::string& src_recv_data, size_t bytes_read);
		size_t getBytesRecv() const;
		void parseRecvData();
		bool setSendData();
		void setClientFd(int fd);
		int getClientFd() const;
		void setMethod(const std::string &method);
		std::string getMethod() const;
		void setPath(const std::string &path);
		std::string getPath() const;
		void setHttpVersion(const std::string &http_version);
		std::string getHttpVersion() const;
		void setBody(const std::string &body);
		std::string getBody() const;
		void setStatusCode(ssize_t code);
		ssize_t getStatusCode() const;
		void setUri(const std::string &uri);
		std::string getUri() const;
		std::string decodeChunked(const std::string &chunkedBody);
		std::map<std::string, std::string> getParameters() const;
		std::map<std::string, std::string> getHeaders() const;
		std::string getFilename() const;
		void setFilename(const std::string &filename);
		bool isMultipart() const;
		std::string getBoundary() const;
		std::map<std::string, std::string> getUploadedFiles() const;
		void parseMultipartFormData();
		void reset();
    	bool processReceivedData(const char* data, size_t bytes_read, bool& receiving_body, size_t& expected_body_size);
        bool areHeadersComplete() const;
        void parseHeaders();
        size_t getRemainingBodySize() const;
        std::map<std::string, std::string> getCookies() const;
        void parseCookies();
        std::string getCookie(const std::string& name) const;
        std::string getSessionId() const;
		size_t getMaxBodySize() const;
};

#endif
