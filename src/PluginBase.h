#pragma once

#include <cstring>  /* for strcmp() */
#include <cstdio>   /* for *printf() */
#include <cstdlib>  /* for free() */
#include <unistd.h> /* for close() */

#include "ConfigParser.h"


// declared in main.cpp
extern Config config;

inline void readFileUnsignedLong(unsigned long* var, const char* path) {
    FILE *f = fopen(path, "r");
    if (!f)
        throw 1;
    fscanf(f, "%lu", var);
    fclose(f);
}

inline void readFileInt(int* var, const char* path) {
    FILE *f = fopen(path, "r");
    if (!f)
        throw 1;
    fscanf(f, "%i", var);
    fclose(f);
}

inline void readFileStr(char* buffer, int size, const char* path) {
    FILE *f = fopen(path, "r");
    if (!f)
        throw 1;
    fgets(buffer, size, f);
    fclose(f);
}


class Plugin {
    protected:
        const char* name = "<no-name-plugin>";
        const char* format;
        bool failed = false;
        unsigned int timeout = 1;
        unsigned int timeoutOffset = 0;
        char* statusLine = NULL;

    public:
        const char* getName(void) {return name;};
        unsigned int getTimeout(void) {return timeout;};
        void setTimeout(unsigned int timeout) {this->timeout = timeout;};
        unsigned int getTimeoutOffset(void) {return timeoutOffset;};
        void setTimeoutOffset(unsigned int offset) {this->timeoutOffset = offset;};
        char* getStatusLine(void) {return statusLine;};

        // main method - redefine in subclasses
        virtual void update(void) {};
};
