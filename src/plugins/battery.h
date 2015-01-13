#pragma once

#include <fstream>

#include "plugin.h"

class PluginBattery : public Plugin {
    private:
        std::ifstream fsFull;
        std::ifstream fsNow;
        std::ifstream fsState;
    public:
        PluginBattery(std::string formatString);
        void update(void);
};

