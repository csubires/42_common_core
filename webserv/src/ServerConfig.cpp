#include "../includes/ServerConfig.hpp"

ServerConfig::ServerConfig() : host(""), ports(), root(""), errorPages(), indexFiles(), maxBodySize(MAX_BODY_SIZE) {}

ServerConfig::ServerConfig(const ServerConfig &other) {
    *this = other;
}

ServerConfig &ServerConfig::operator=(const ServerConfig &other) {
    if (this != &other) {
        this->host = other.host;
        this->ports = other.ports;
        this->root = other.root;
        this->errorPages = other.errorPages;
        this->indexFiles = other.indexFiles;
        this->maxBodySize = other.maxBodySize;
    }
    return *this;
}

ServerConfig::~ServerConfig() {}

std::string ServerConfig::getHost() const {
    return host;
}

std::vector<int> ServerConfig::getPorts() const {
    return ports;
}

void ServerConfig::setHost(const std::string &host) {
    this->host = host;
}

void ServerConfig::setPorts(int port) {
    this->ports.push_back(port);
}

std::string ServerConfig::getRoot() const {
    return root;
}

void ServerConfig::setRoot(const std::string &root) {
    this->root = root;
}

std::vector<std::pair<std::string, int> > ServerConfig::getErrorPages() const {
    return errorPages;
}

void ServerConfig::addErrorPage(const std::string &errorPage, int errorCode) {
    errorPages.push_back(std::make_pair(errorPage, errorCode));
}

std::vector<std::string> ServerConfig::getIndexFiles() const {
    return indexFiles;
}

void ServerConfig::addIndexFile(const std::string &indexFile) {
    indexFiles.push_back(indexFile);
}

size_t ServerConfig::getMaxBodySize() const {
    return maxBodySize;
}

void ServerConfig::setMaxBodySize(size_t maxBodySize) {
    this->maxBodySize = maxBodySize;
}

std::vector<std::string> ServerConfig::getMethods() const {
    return methods;
}

void ServerConfig::setMethods(const std::vector<std::string> &methods) {
	this->methods = methods;
}
