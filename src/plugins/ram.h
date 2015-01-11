#pragma once

#include <fstream>

#include "plugin.h"

class PluginRAM : public Plugin {
    private:
        ifstream meminfo;
        long unitFactor;
    public:
        PluginRAM(std::string formatString);
        void update(void);
};

