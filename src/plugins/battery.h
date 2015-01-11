#pragma once

#include <fstream>

#include "plugin.h"

class PluginBattery : public Plugin {
    private:
        ifstream fsFull;
        ifstream fsNow;
        ifstream fsState;
    public:
        PluginBattery(std::string formatString);
        void update(void);
};

