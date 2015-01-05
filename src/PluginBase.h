#pragma once

#include <string>
#include <fstream>

#include <format.h>  // cppformat

// TODO
#include "ConfigParser.h"
extern Config config;


template<typename ValueType>
inline void castValueFromFile(const char* path, ValueType & value)
{
    std::ifstream fs(path);
    fs >> value;
}


class Plugin {
    protected:
        std::string name;
        bool failed = false;
        unsigned int timeout = 1;
        unsigned int timeoutOffset = 0;
        std::string formatString;
        std::string statusLine;

    public:
        Plugin(std::string name, std::string formatString)
            : name(name), formatString(formatString) {};

        std::string getName(void) { return name; };
        bool isFailed(void) { return failed; };
        unsigned int getTimeout(void) { return timeout; };
        void setTimeout(unsigned int timeout) { this->timeout = timeout; };
        unsigned int getTimeoutOffset(void) { return timeoutOffset; };
        void setTimeoutOffset(unsigned int offset) { this->timeoutOffset = offset; };
        std::string getStatusLine(void) { return statusLine; };

        // main method - redefine in subclasses
        virtual void update(void) {};
};
