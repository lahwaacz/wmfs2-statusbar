#pragma once

#include <fstream>

#include "plugin.h"

class PluginCPU : public Plugin {
    private:
        unsigned long idleOld;
        unsigned long totalOld;
        ifstream fsStat;
    public:
        PluginCPU(std::string formatString);
        void update(void);
};

