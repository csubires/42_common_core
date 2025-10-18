#ifndef RESPONSEHEADER_HPP
#define RESPONSEHEADER_HPP

#include "Webserv.hpp"

#define RESPONSE_200 "HTTP/1.1 200 OK\r\nContent-Type: {}\r\nContent-Length: {}\r\nConnection: {}\r\n\r\n"
#define RESPONSE_201 "HTTP/1.1 201 Created\r\nContent-Type: text/html\r\nContent-Length: {}\r\nLocation: {}\r\nConnection: {}\r\n\r\n"
#define RESPONSE_204 "HTTP/1.1 204 No Content\r\nContent-Type: text/html\r\nContent-Length: 0\r\nLocation: {}\r\nConnection: {}\r\n\r\n"
#define RESPONSE_301 "HTTP/1.1 301 Moved Permanently\r\nLocation: {}\r\nContent-Length: 0\r\nConnection: {}\r\n\r\n"
#define RESPONSE_307 "HTTP/1.1 307 Temporary Redirect\r\nLocation: {}/\r\nContent-Length: 0\r\nConnection: {}\r\n\r\n"
#define RESPONSE_400 "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\nContent-Length: {}\r\nConnection: close\r\n\r\n"
#define RESPONSE_403 "HTTP/1.1 403 Forbidden\r\nContent-Type: text/html\r\nContent-Length: {}\r\nConnection: close\r\n\r\n"
#define RESPONSE_404 "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: {}\r\nConnection: close\r\n\r\n"
#define RESPONSE_405 "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/html\r\nContent-Length: {}\r\nConnection: close\r\n\r\n"
#define RESPONSE_413 "HTTP/1.1 413 Payload Too Large\r\nContent-Type: text/html\r\nContent-Length: {}\r\nConnection: close\r\n\r\n"
#define RESPONSE_500 "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\nContent-Length: {}\r\nConnection: close\r\n\r\n"
#define RESPONSE_502 "HTTP/1.1 502 Bad Gateway\r\nContent-Type: text/html\r\nContent-Length: {}\r\nConnection: close\r\n\r\n"
#define RESPONSE_503 "HTTP/1.1 503 Service Unavailable\r\nContent-Type: text/html\r\nContent-Length: {}\r\nConnection: close\r\n\r\n"
#define RESPONSE_504 "HTTP/1.1 504 Gateway Timeout\r\nContent-Type: text/html\r\nContent-Length: {}\r\nConnection: close\r\n\r\n"
#define RESPONSE_520 "HTTP/1.1 520 Web Server Returned an Unknown Error\r\nContent-Type: text/html\r\nContent-Length: {}\r\nConnection: close\r\n\r\n"

class ResponseHeader {
	public:
		ResponseHeader();
		~ResponseHeader();

		const std::string	getHeader(size_t status_code);
		void				setContentType(std::string path);
		void				setContentLength(size_t size);
		void				setLocation(std::string location);

	private:
		std::string			header;
		std::string			contentType;
		ssize_t				contentLength;
		std::string			date;
		std::string			server;
		std::string			location;

		ResponseHeader(const ResponseHeader& obj);
		const std::string	setContent(size_t status_code);
		void				setDate();
};

#endif
