#ifndef CONFIG_PARSING_HPP
#define CONFIG_PARSING_HPP

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <cstdlib>
#include "LocationConfig.hpp"
#include "ServerConfig.hpp"
#include "utils.hpp"

class ConfigParsing {
    private:
        std::vector<ServerConfig *> servers;
        std::map<ServerConfig *, std::vector<LocationConfig *> > locations;
        std::string configFile;

    public:
        ConfigParsing();
        ConfigParsing(const ConfigParsing &other);
        ConfigParsing &operator=(const ConfigParsing &other);
        ~ConfigParsing();

        bool isFileReadable(const std::string &filePath);
        std::vector<std::string> tokenize(const std::string &content, const std::string &delimiters);
        void parse(std::vector<std::string> &tokens);
        void setConfigFile(const std::string &configFile);
        std::string getConfigFile() const;
        std::vector<ServerConfig *> getServers() const;
		const std::map<ServerConfig *, std::vector<LocationConfig*> >& getLocations() const;
        void printConfig() const;
};

#endif