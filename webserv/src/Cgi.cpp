#include "../includes/Cgi.hpp"
#include "../includes/utils.hpp"
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctime>
#include <cerrno>
#include <cstring>

Cgi::Cgi(const std::string &scriptPath, const std::map<std::string, std::string> &env, std::vector<std::pair<std::string, std::string> > cgi)
    : scriptPath(scriptPath), env(env), output(""), postData(""), status(0), cgi(cgi) {}

Cgi::Cgi(const Cgi &other)
    : scriptPath(other.scriptPath), env(other.env), output(other.output), postData(other.postData), status(other.status), cgi(other.cgi) {}

Cgi &Cgi::operator=(const Cgi &other) {
    if (this != &other) {
        scriptPath = other.scriptPath;
        env = other.env;
        output = other.output;
        postData = other.postData;
        status = other.status;
        cgi = other.cgi;
    }
    return *this;
}

Cgi::~Cgi() {}

bool Cgi::execute() {
    int inPipe[2];
    int outPipe[2];
    pid_t pid;

    logger(STDOUT_FILENO, DEBUG, "Executing CGI: " + scriptPath);
    logger(STDOUT_FILENO, DEBUG, "Interpreter: " + getInterpreter());

    if (pipe(inPipe) == -1 || pipe(outPipe) == -1) {
        logger(STDOUT_FILENO, ERROR, "Failed to create pipes for CGI");
        return false;
    }
    pid = fork();
    if (pid < 0) {
        logger(STDOUT_FILENO, ERROR, "Failed to fork process for CGI");
        return false;
    }
    if (pid == 0) {
        close(inPipe[1]);
        close(outPipe[0]);

        dup2(inPipe[0], STDIN_FILENO);
        dup2(outPipe[1], STDOUT_FILENO);
        close(inPipe[0]);
        close(outPipe[1]);

        size_t lastSlash = scriptPath.rfind('/');
        if (lastSlash != std::string::npos) {
            std::string dir = scriptPath.substr(0, lastSlash);
            if (chdir(dir.c_str()) != 0) {
                logger(STDOUT_FILENO, ERROR, "Failed to change directory for CGI: " + dir);
                throw ;
            }
        }

        std::vector<char*> envp;
        for (std::map<std::string, std::string>::const_iterator it = env.begin(); it != env.end(); ++it) {
            std::string envVar = it->first + "=" + it->second;
            envp.push_back(strdup(envVar.c_str()));
        }
        envp.push_back(NULL);

        std::string interpreter = getInterpreter();
        std::vector<char*> argv;

        if (!interpreter.empty()) {
            std::string interpreterPath;
            std::vector<std::string> paths;
            paths.push_back(interpreter);
            paths.push_back("/usr/bin/" + interpreter);
            paths.push_back("/bin/" + interpreter);
            paths.push_back("/usr/local/bin/" + interpreter);

            for (size_t i = 0; i < paths.size(); ++i) {
                if (access(paths[i].c_str(), X_OK) == 0) {
                    interpreterPath = paths[i];
                    break;
                }
            }

            if (interpreterPath.empty()) {
                logger(STDOUT_FILENO, ERROR, "CGI interpreter not found: " + interpreter);
                throw ;
            }

            argv.push_back(strdup(interpreterPath.c_str()));
            argv.push_back(strdup(scriptPath.c_str()));
        } else {
            argv.push_back(strdup(scriptPath.c_str()));
        }
        argv.push_back(NULL);

        if (!interpreter.empty()) {
            if (execve(argv[0], argv.data(), envp.data()) == -1) {
                logger(STDOUT_FILENO, ERROR, "Failed to execute CGI interpreter: " + std::string(argv[0]) + " - " + strerror(errno));
                throw ;
            }
        } else {
            if (execve(scriptPath.c_str(), argv.data(), envp.data()) == -1) {
                logger(STDOUT_FILENO, ERROR, "Failed to execute CGI script: " + scriptPath + " - " + strerror(errno));
                throw ;
            }
        }
		for (size_t i = 0; i < envp.size(); ++i)
			free(envp[i]);
		for (size_t i = 0; i < argv.size(); ++i)
			free(argv[i]);
		throw ;
    } else {
        close(inPipe[0]);
        close(outPipe[1]);
        if (!postData.empty())
            write(inPipe[1], postData.c_str(), postData.size());
        close(inPipe[1]);

        char buffer[4096];
        ssize_t bytesRead;
        output.clear();
        while ((bytesRead = read(outPipe[0], buffer, sizeof(buffer))) > 0) {
            output.append(buffer, bytesRead);
        }
        close(outPipe[0]);

        int wstatus;
        pid_t result = waitpid(pid, &wstatus, WNOHANG);
        time_t start_time = time(NULL);

        while (result == 0 && (time(NULL) - start_time) < 30) {
            usleep(100000);
            result = waitpid(pid, &wstatus, WNOHANG);
        }

        if (result == 0) {
            kill(pid, SIGTERM);
            usleep(100000);
            kill(pid, SIGKILL);
            waitpid(pid, &wstatus, 0);
            logger(STDOUT_FILENO, ERROR, "CGI script timed out");
            return false;
        } else if (result == -1) {
            logger(STDOUT_FILENO, ERROR, "waitpid failed: " + std::string(strerror(errno)));
            return false;
        }

        if (WIFEXITED(wstatus)) {
            status = WEXITSTATUS(wstatus);
            if (status != 0) {
                logger(STDOUT_FILENO, ERROR, "CGI script exited with status: " + stringify(status));
            }
            return status == 0;
        } else if (WIFSIGNALED(wstatus)) {
            int signal = WTERMSIG(wstatus);
            logger(STDOUT_FILENO, ERROR, "CGI script terminated by signal: " + stringify(signal));
            return false;
        } else {
            logger(STDOUT_FILENO, ERROR, "CGI script did not terminate normally");
            return false;
        }
    }
    return true;
}

std::string Cgi::getOutput() const {
    return output;
}

int Cgi::getStatus() const {
    return status;
}

int Cgi::checkExtension() {
	size_t dotPos = scriptPath.rfind('.');
	if (dotPos == std::string::npos)
		return -1;

	std::string ext = scriptPath.substr(dotPos);

	std::string interpreter = getInterpreter();
	if (interpreter.empty())
		return -1;

	std::string command = "which " + interpreter + " > /dev/null 2>&1";
	return (std::system(command.c_str()) == 0) ? 0 : -1;
}

void Cgi::handleCookies(std::map<std::string, std::string> &headers) {
    size_t pos = 0;
    while ((pos = output.find("Set-Cookie:", pos)) != std::string::npos) {
        size_t endPos = output.find("\r\n", pos);
        if (endPos == std::string::npos)
            break;
        std::string cookie = output.substr(pos + 11, endPos - (pos + 11));
        headers["Set-Cookie"] = cookie;
        pos = endPos + 2;
    }
}

void Cgi::setPostData(const std::string &data) {
    postData = data;
}

void Cgi::setupEnvironment(const std::string &method, const std::string &uri,
                         const std::string &queryString, const std::string &contentType,
                         size_t contentLength, const std::string &serverName,
                         const std::string &serverPort, const std::map<std::string, std::string> &headers) {

    env["REQUEST_METHOD"] = method;
    env["REQUEST_URI"] = uri;
    env["QUERY_STRING"] = queryString;
    env["CONTENT_TYPE"] = contentType;
    env["CONTENT_LENGTH"] = stringify(contentLength);
    env["SERVER_NAME"] = serverName;
    env["SERVER_PORT"] = serverPort;
    env["SERVER_SOFTWARE"] = "webserv/1.0";
    env["GATEWAY_INTERFACE"] = "CGI/1.1";
    env["SERVER_PROTOCOL"] = "HTTP/1.1";
 	env["SCRIPT_FILENAME"] = scriptPath;

    size_t scriptNamePos = uri.rfind('/');
    if (scriptNamePos != std::string::npos)
        env["SCRIPT_NAME"] = uri.substr(scriptNamePos);
    else
        env["SCRIPT_NAME"] = uri;

    size_t lastSlash = scriptPath.rfind('/');
    if (lastSlash != std::string::npos)
        env["DOCUMENT_ROOT"] = scriptPath.substr(0, lastSlash);
    else
        env["DOCUMENT_ROOT"] = ".";

    std::string scriptName = env["SCRIPT_NAME"];
    size_t scriptPos = uri.find(scriptName);
    if (scriptPos != std::string::npos) {
        std::string pathInfo = uri.substr(scriptPos + scriptName.length());
        if (!pathInfo.empty()) {
            env["PATH_INFO"] = pathInfo;
            env["PATH_TRANSLATED"] = env["DOCUMENT_ROOT"] + pathInfo;
        }
    }

    for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it) {
        std::string headerName = "HTTP_" + it->first;
        for (size_t i = 0; i < headerName.length(); ++i) {
            if (headerName[i] == '-')
                headerName[i] = '_';
            else
                headerName[i] = std::toupper(headerName[i]);
        }
        env[headerName] = it->second;
    }

    logger(STDOUT_FILENO, DEBUG, "CGI Environment:");
    logger(STDOUT_FILENO, DEBUG, "  SCRIPT_FILENAME: " + env["SCRIPT_FILENAME"]);
    logger(STDOUT_FILENO, DEBUG, "  SCRIPT_NAME: " + env["SCRIPT_NAME"]);
    logger(STDOUT_FILENO, DEBUG, "  DOCUMENT_ROOT: " + env["DOCUMENT_ROOT"]);
}

std::string Cgi::getInterpreter() const {
    size_t dotPos = scriptPath.rfind('.');
    if (dotPos == std::string::npos)
        return "";
    std::string ext = scriptPath.substr(dotPos);

    std::vector<std::pair<std::string, std::string> > cgiConfig = cgi;
    for (size_t i = 0; i <= cgiConfig.size(); i++) {
        if (cgiConfig[i].first == ext)
            return cgiConfig[i].second;
    }
    return "";
}

std::string Cgi::parseHeaders(std::string &body) {
    std::string headers;
    size_t headerEnd = output.find("\r\n\r\n");
    if (headerEnd != std::string::npos) {
        headers = output.substr(0, headerEnd);
        body = output.substr(headerEnd + 4);
    } else {
        headers = "";
        body = output;
    }
    return headers;
}
