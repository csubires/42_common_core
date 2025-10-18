#ifndef LOCATION_CONFIG_HPP
#define LOCATION_CONFIG_HPP

#include <iostream>
#include <string>
#include <vector>
#include "ServerConfig.hpp"

class LocationConfig {
    private:
        std::string filePath;
        std::string locationPath;
        bool autoIndex;
        std::vector<std::pair<std::string, std::string> > redirects;
        std::vector<std::string> tryFiles;
        std::vector<std::string> cgiIncludes;
        std::string fastcgiPass;
        std::string fastcgiIndex;
		std::string upload_path;
        std::vector<std::pair<std::string, std::string> > fastcgiParams;
        bool cgiEnabled;
	    std::vector<std::pair<std::string, std::string> > cgi;
        size_t maxBodySize;
        std::vector<std::string> methods;
        std::string root;

    public:
        LocationConfig();
        LocationConfig(ServerConfig* server);
        LocationConfig(const LocationConfig &other);
        LocationConfig &operator=(const LocationConfig &other);
        ~LocationConfig();

        std::string getFilePath() const;
        void setFilePath(const std::string &filePath);
        std::string getLocationPath() const;
        void setLocationPath(const std::string &locationPath);
        bool getAutoIndex() const;
        void setAutoIndex(const std::string &autoIndex);
        void addRedirect(const std::string &oldPath, const std::string &newPath);
        std::vector<std::pair<std::string, std::string> > getRedirects() const;
        std::vector<std::string> getTryFiles() const;
        void addTryFile(const std::string &tryFile);
        std::vector<std::string> getCgiIncludes() const;
        void addCgiInclude(const std::string &include);
        std::string getFastcgiPass() const;
        void setFastcgiPass(const std::string &fastcgiPass);
        std::string getFastcgiIndex() const;
        void setFastcgiIndex(const std::string &fastcgiIndex);
        std::vector<std::pair<std::string, std::string> > getFastcgiParams() const;
        void addFastcgiParam(const std::string &param, const std::string &value);
        bool getCgiEnabled() const;
        void setCgiEnabled(bool enabled);
        std::vector<std::pair<std::string, std::string> > getCgi() const;
        void addCgi(const std::string &extension, const std::string &interpreter);
        size_t getMaxBodySize() const;
        void setMaxBodySize(const size_t &maxBodySize);
        std::vector<std::string> getMethods() const;
        void addMethods(const std::vector<std::string> &methods);
        std::string getRoot() const;
        void setRoot(const std::string &root);
		std::string getUploadPath() const;
		void setUploadPath(const std::string &uploadPath);
};

#endif
