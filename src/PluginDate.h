#pragma once

#include "PluginBase.h"

#include <ctime>

class PluginDate : public Plugin {
    private:
        struct tm *tm;
        time_t t;
        char date[128] = {0};

    public:
        PluginDate(void);
        void update(void);
};

