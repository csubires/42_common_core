#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <sys/stat.h> // pathIsFile

#define LOG_FILE			3
#define DEFAULT_ERROR_LOG	"./logger.log"
#ifndef DEBUG_MODE
#define DEBUG_MODE		false
#endif

enum PathType {
	PATH_NOT_EXISTS = 0,
	PATH_IS_FILE = 1,
	PATH_IS_DIRECTORY = 2,
	PATH_IS_OTHER = 3,
	PATH_NO_PERMISSION = 4,
	PATH_ERROR = 5
};

enum e_message {
	ERROR,
	WARNING,
	INFO,
	DEBUG,
	SUCCESS,
	UNKNOWN
};

template<typename T>
std::string stringify(const T& value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

void		logger(int out, e_message type, const std::string& message);
std::string trim(const std::string& str);
std::string format_string(const std::string& format, const std::vector<std::string>& args);
PathType	checkPath(const std::string& path);
bool		pathIsFile(const std::string& path);
bool		pathIsDirectory(const std::string& path);
bool		pathExists(const std::string& path);
bool		pathIsAccessible(const std::string& path);
std::string	normalizePath(const std::string& path);

#endif
