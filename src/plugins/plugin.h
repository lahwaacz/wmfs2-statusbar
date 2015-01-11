#pragma once

#include <string>

#include <format.h>  // cppformat

// TODO
#include "../config.h"
extern Config config;

class Plugin {
    protected:
        const std::string name;
        bool failed = false;
        unsigned timeout = 1;
        unsigned timeoutOffset = 0;
        std::string formatString;
        std::string statusLine;

    public:
        Plugin(std::string name, std::string formatString)
            : name(name), formatString(formatString) {};

        std::string getName(void) { return name; };
        bool isFailed(void) { return failed; };
        unsigned int getTimeout(void) { return timeout; };
        void setTimeout(const unsigned timeout) { this->timeout = timeout; };
        unsigned int getTimeoutOffset(void) { return timeoutOffset; };
        void setTimeoutOffset(const unsigned offset) { this->timeoutOffset = offset; };
        std::string getStatusLine(void) { return statusLine; };

        // main method - redefine in subclasses
        virtual void update(void) {};
};
