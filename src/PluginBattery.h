#pragma once

#include "PluginBase.h"

class PluginBattery : public Plugin {
    private:
        unsigned long full = 0;
        unsigned long now = 0;
        const char* pathFull;
        const char* pathNow;
        const char* pathState;
        int criticalPercent;
        const char* criticalAction;
    public:
        PluginBattery(void);
        void update(void);
};

