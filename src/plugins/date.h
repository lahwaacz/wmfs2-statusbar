#pragma once

#include <ctime>

#include "plugin.h"

class PluginDate : public Plugin {
    private:
        struct tm *tm;
        time_t t;
        char date[128] = {0};

    public:
        PluginDate(std::string formatString);
        void update(void);
};

