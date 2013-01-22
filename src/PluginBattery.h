#pragma once

#include "PluginBase.h"

class PluginBattery : public Plugin {
    private:
        unsigned long full = 0;
        unsigned long now = 0;
    public:
        PluginBattery(void);
        void update(void);
};

