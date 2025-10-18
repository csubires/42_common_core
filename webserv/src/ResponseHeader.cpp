#include "../includes/ResponseHeader.hpp"
#include "../includes/utils.hpp"
#include "../includes/ContentTypes.hpp"

ResponseHeader::ResponseHeader() : contentType(""), date(""), server(SERVER_NAME) {}

ResponseHeader::~ResponseHeader() {}

const std::string ResponseHeader::setContent(size_t status_code) {
	std::string content;
	content.clear();
	std::vector<std::string> args;
	args.clear();

	std::string connectionHeader = "close";
	if (status_code < 400 && status_code != 204)
		connectionHeader = "keep-alive";

	switch (status_code)
	{
		case 200:
			args.push_back(contentType);
			args.push_back(stringify(contentLength));
			args.push_back(connectionHeader);
			content.append(format_string(RESPONSE_200, args));
			break;
		case 201:
			args.push_back(stringify(contentLength));
			args.push_back(location);
			args.push_back(connectionHeader);
			content.append(format_string(RESPONSE_201, args));
			break;
		case 204:
			args.push_back(stringify(contentLength));
			args.push_back(location);
			args.push_back(connectionHeader);
			content.append(format_string(RESPONSE_204, args));
			break;
		case 301:
			args.push_back(location);
			args.push_back(connectionHeader);
			content.append(format_string(RESPONSE_301, args));
			break;
		case 307:
			args.push_back(location);
			args.push_back(connectionHeader);
			content.append(format_string(RESPONSE_307, args));
			break;
		case 400:
			args.push_back(stringify(contentLength));
			content.append(format_string(RESPONSE_400, args));
			break;
		case 403:
			args.push_back(stringify(contentLength));
			content.append(format_string(RESPONSE_403, args));
			break;
		case 404:
			args.push_back(stringify(contentLength));
			content.append(format_string(RESPONSE_404, args));
			break;
		case 405:
			args.push_back(stringify(contentLength));
			content.append(format_string(RESPONSE_405, args));
			break;
		case 413:
			args.push_back(stringify(contentLength));
			content.append(format_string(RESPONSE_413, args));
			break;
		default:
			args.push_back(stringify(contentLength));
			content.append(format_string(RESPONSE_500, args));
			break;
	}
	return (content);
}

void ResponseHeader::setContentType(std::string path)
{
	std::string extension;
	size_t has_dot = path.find_last_of(".");

	if (has_dot != std::string::npos && has_dot < path.length() - 1)
		extension = path.substr(path.rfind(".") + 1, path.size() - path.rfind("."));

	contentType = ContentTypes::getType(extension);
}

void ResponseHeader::setDate()
{
	char buffer[100];
	struct timeval tv;
	struct tm *tm;

	gettimeofday(&tv, NULL);
	tm = gmtime(&tv.tv_sec);
	strftime(buffer, 100, "%a, %d %b %Y %H:%M:%S GMT", tm);
	date = std::string(buffer);
}

void ResponseHeader::setContentLength(size_t size) {
	contentLength = size;
}

void ResponseHeader::setLocation(std::string location) {
	this->location = location;
}

const std::string ResponseHeader::getHeader(size_t status_code) {
	setDate();
	return (setContent(status_code));
}
