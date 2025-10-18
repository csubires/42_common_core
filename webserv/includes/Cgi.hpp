#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include <map>
#include <cstring>
#include <sys/wait.h> // waitpid
#include <cstdlib>
#include <unistd.h> // chdir
#include <vector>

class Cgi {
    private:
        std::string scriptPath;
        std::map<std::string, std::string> env;
        std::string output;
        std::string postData;
        int status;
        std::vector<std::pair<std::string, std::string> > cgi;

    public:
        Cgi(const std::string &scriptPath, const std::map<std::string, std::string> &env, std::vector<std::pair<std::string, std::string> > cgi);
        Cgi(const Cgi &other);
        Cgi &operator=(const Cgi &other);
        ~Cgi();

        bool execute();
        std::string getOutput() const;
        int getStatus() const;
        int checkExtension();
        void handleCookies(std::map<std::string, std::string> &headers);
        void setPostData(const std::string &data);
        void setupEnvironment(const std::string &method, const std::string &uri,
                            const std::string &queryString, const std::string &contentType,
                            size_t contentLength, const std::string &serverName,
                            const std::string &serverPort, const std::map<std::string, std::string> &headers);
        std::string getInterpreter() const;
        std::string parseHeaders(std::string &body);
};

#endif
