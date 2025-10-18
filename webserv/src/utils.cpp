#include "../includes/utils.hpp"

void logger(int out, e_message type, const std::string& message) {

	if (type == DEBUG && !DEBUG_MODE)
		return;
	std::string safe_message = message;
	const char* color_reset = "\033[0m";
	static const char* colors[] = {"\033[1;31m", "\033[1;33m", "\033[1;34m", "\033[1;35m", "\033[1;32m"};
	static const char* prefixes[] = {"[ERROR] ", "[WARNING] ", "[INFO] ", "[DEBUG] ", "[SUCCESS] ", "[UNKNOWN] ", };

	switch (out) {
		case STDOUT_FILENO:
			std::cout << colors[type] << prefixes[type] << color_reset << safe_message << std::endl << std::flush;
			break;
		case STDERR_FILENO:
			std::cerr << prefixes[type] << safe_message << color_reset << std::endl << std::flush;
			break;
		case LOG_FILE:
			{
				std::ofstream file(DEFAULT_ERROR_LOG, std::ios::app);
				if (file.is_open()) {
					file << prefixes[type] << safe_message << std::endl << std::flush;
					file.close();
				} else {
					std::cerr << "[ERROR] Logger " << std::endl << std::flush;
				}
			}
			break;
		default:
			std::cerr << "[ERROR] Unknown out: " << out << std::endl << std::flush;
			break;
	}
}

std::string format_string(const std::string& format, const std::vector<std::string>& args) {
	std::string			result = format;
	std::stringstream	ss;

	for (size_t i = 0; i < args.size(); ++i) {
		size_t pos = result.find("{}");
		if (pos != std::string::npos)
			result.replace(pos, 2, args[i]);
	}
	return (result);
}

std::string trim(const std::string& str) {
	size_t first = str.find_first_not_of(" \t\n\r");
	if (first == std::string::npos) {
		return ("");
	}
	size_t last = str.find_last_not_of(" \t\n\r");
	return (str.substr(first, last - first + 1));
}

PathType checkPath(const std::string& path) {
	struct stat s;

	if (stat(path.c_str(), &s)) {
		struct stat s2;
		if (!lstat(path.c_str(), &s2)) {
			return (PATH_NO_PERMISSION);
		} else {
			if (errno == ENOENT)
				return (PATH_NOT_EXISTS);
			else if (errno == EACCES)
				return (PATH_NO_PERMISSION);
			else
				return (PATH_ERROR);
		}
	}

	if (S_ISREG(s.st_mode))
		return (PATH_IS_FILE);
	else if (S_ISDIR(s.st_mode))
		return (PATH_IS_DIRECTORY);
	else
		return (PATH_IS_OTHER);
}

bool pathIsFile(const std::string& path) {
	return (checkPath(path) == (PATH_IS_FILE));
}


bool pathIsDirectory(const std::string& path) {
	return (checkPath(path) == (PATH_IS_DIRECTORY));
}

bool pathExists(const std::string& path) {
	PathType result = checkPath(path);
	return (result == PATH_IS_FILE ||
			result == PATH_IS_DIRECTORY ||
			result == PATH_IS_OTHER ||
			result == PATH_NO_PERMISSION);
}

bool pathIsAccessible(const std::string& path) {
	PathType result = checkPath(path);
	return (result == PATH_IS_FILE ||
			result == PATH_IS_DIRECTORY ||
			result == PATH_IS_OTHER);
}

std::string normalizePath(const std::string& path) {
	if (path.empty())
		return ("/");

	std::string result = path;
	size_t start = (result.size() > 1 && result[0] == '/' && result[1] == '/') ? 2 : 0;
	size_t pos;

	while ((pos = result.find("//", start)) != std::string::npos) {
		result.replace(pos, 2, "/");
	}
	while ((pos = result.find("/./")) != std::string::npos) {
		result.replace(pos, 3, "/");
	}
	return (result);
}
