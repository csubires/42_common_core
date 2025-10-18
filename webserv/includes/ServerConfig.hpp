#ifndef SERVER_CONFIG_HPP
#define SERVER_CONFIG_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Webserv.hpp"

class ServerConfig {
    private:
        std::string host;
        std::vector<int> ports;
        std::string root;
        std::vector<std::pair<std::string, int> > errorPages;
        std::vector<std::string> indexFiles;
        size_t maxBodySize;
        std::vector<std::string> methods;

    public:
        ServerConfig();
        ServerConfig(const ServerConfig &other);
        ServerConfig &operator=(const ServerConfig &other);
        ~ServerConfig();

        std::string getHost() const;
        void setHost(const std::string &host);
        std::vector<int> getPorts() const;
        void setPorts(int port);
        std::string getRoot() const;
        void setRoot(const std::string &root);
        std::vector<std::pair<std::string, int> > getErrorPages() const;
        void addErrorPage(const std::string &errorPage, int errorCode);
        std::vector<std::string> getIndexFiles() const;
        void addIndexFile(const std::string &indexFile);
        size_t getMaxBodySize() const;
        void setMaxBodySize(size_t maxBodySize);
        std::vector<std::string> getMethods() const;
        void setMethods(const std::vector<std::string> &methods);
};

#endif