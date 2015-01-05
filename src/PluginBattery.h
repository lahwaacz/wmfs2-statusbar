#pragma once

#include "PluginBase.h"

class PluginBattery : public Plugin {
    private:
        unsigned long full = 0;
        unsigned long now = 0;
        const char *pathFull;
        const char *pathNow;
        const char *pathState;
    public:
        PluginBattery(std::string formatString);
        void update(void);
};

