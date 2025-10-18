#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <cstring>
#include <dirent.h>
#include "Webserv.hpp"
#include "ResponseHeader.hpp"
#include "ServerConfig.hpp"
#include "LocationConfig.hpp"
#include "Request.hpp"
#include "Cgi.hpp"

#define ERROR_400_HTML "<html><body style=\"font-family:Arial,sans-serif;text-align:center;padding:50px\"><h1 style=\"color:#d32f2f\">400 Bad Request</h1><p>Your browser sent a request that this server could not understand.</p><hr><p>Webserv/42.0</p></body></html>"
#define ERROR_403_HTML "<html><body style=\"font-family:Arial,sans-serif;text-align:center;padding:50px\"><h1 style=\"color:#d32f2f\">403 Forbidden</h1><p>You don't have permission to access this resource.</p><hr><p>Webserv/42.0</p></body></html>"
#define ERROR_404_HTML "<html><body style=\"font-family:Arial,sans-serif;text-align:center;padding:50px\"><h1 style=\"color:#d32f2f\">404 Not Found</h1><p>The requested URL was not found on this server.</p><hr><p>Webserv/42.0</p></body></html>"
#define ERROR_405_HTML "<html><body style=\"font-family:Arial,sans-serif;text-align:center;padding:50px\"><h1 style=\"color:#d32f2f\">405 Method Not Allowed</h1><p>The requested method is not allowed for this URL.</p><hr><p>Webserv/42.0</p></body></html>"
#define ERROR_413_HTML "<html><body style=\"font-family:Arial,sans-serif;text-align:center;padding:50px\"><h1 style=\"color:#d32f2f\">413 Payload Too Large</h1><p>The request body exceeds the maximum allowed size.</p><hr><p>Webserv/42.0</p></body></html>"
#define ERROR_500_HTML "<html><body style=\"font-family:Arial,sans-serif;text-align:center;padding:50px\"><h1 style=\"color:#d32f2f\">500 Internal Server Error</h1><p>The server encountered an internal error and could not complete your request.</p><hr><p>Webserv/42.0</p></body></html>"
#define ERROR_502_HTML "<html><body style=\"font-family:Arial,sans-serif;text-align:center;padding:50px\"><h1 style=\"color:#d32f2f\">502 Bad Gateway</h1><p>The server received an invalid response from the upstream server.</p><hr><p>Webserv/42.0</p></body></html>"
#define ERROR_503_HTML "<html><body style=\"font-family:Arial,sans-serif;text-align:center;padding:50px\"><h1 style=\"color:#d32f2f\">503 Service Unavailable</h1><p>The server is temporarily unable to service your request.</p><hr><p>Webserv/42.0</p></body></html>"
#define ERROR_504_HTML "<html><body style=\"font-family:Arial,sans-serif;text-align:center;padding:50px\"><h1 style=\"color:#d32f2f\">504 Gateway Timeout</h1><p>The server did not receive a timely response from the upstream server.</p><hr><p>Webserv/42.0</p></body></html>"
#define ERROR_520_HTML "<html><body style=\"font-family:Arial,sans-serif;text-align:center;padding:50px\"><h1 style=\"color:#d32f2f\">520 Unknown Error</h1><p>The server returned an unknown error.</p><hr><p>Webserv/42.0</p></body></html>"
#define MESSAGE_LOOP "<html><body style=\"font-family:Arial,sans-serif;text-align:center;padding:50px\"><h1 style=\"color:#d32f2f\">500 Internal Server Error</h1><p>Too many redirects or internal loop detected.</p><hr><p>Webserv/42.0</p></body></html>"

class ServerConfig;
class Request;
class ResponseHeader;
class LocationConfig;

class Response {
	public:
		Response(const int client_fd, const Request& request, const ServerConfig& config, const std::vector<LocationConfig*>& locations);
		~Response();
		const char*			getResponse();
		size_t				getSize();
		size_t				getStatusCode() const;
       	void				setSessionCookie(const std::string& session_id);
	   	void				reset();

	private:
		std::string							send_response;
		std::string							send_header;
		std::string							send_body;
		int									client_fd;
		size_t								status_code;
		size_t								bytes_send;
		size_t								counter;
		const Request&						request;
		const ServerConfig&					config;
		ResponseHeader*						response_header;
 		const std::vector<LocationConfig*>&	locations;
		std::map<std::string, std::string>	cookies;

		Response();
		Response(const Response &obj);
		Response &operator=(const Response &obj);

		void				readContent(const std::string &path);
		void				writeContent(const std::string &path, std::string content);
		void				handleFileUpload();
		void				deleteContent(const std::string &path);
		void		 		ListDirectory(const std::string& path, const std::string& uri);
		const std::string	getPathStatusCode();
		LocationConfig*		findLocation(const std::string& path);
		bool				shouldExecuteAsCGI(const std::string &path);
		void				executeCGI(const std::string &path);
		std::string			resolveFilePath(const std::string &uri);
        void				setCookie(const std::string& name, const std::string& value, time_t max_age = 3600, const std::string& path = "/");
        void				removeCookie(const std::string& name);
        std::string			buildCookieHeaders();
};

#endif
