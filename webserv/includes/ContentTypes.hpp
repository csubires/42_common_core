#ifndef CONTENT_TYPES_HPP
#define CONTENT_TYPES_HPP

#include <iostream>
#include <cstring>

class ContentTypes {
    public:
        static const char* getType(const char * path);
        static std::string getType(const std::string &extension);
        static const char *getExtension(const char *type, int skip = 0);
        static std::string getExtension(const std::string &type, int skip = 0);

    private:
        struct entry {
            const char* fileExtension;
            const char* mimeType;
        };
        static ContentTypes::entry types[347];
        static int strcmpi(const char *s1, const char *s2);
};

#endif