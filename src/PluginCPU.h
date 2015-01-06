#pragma once

#include <fstream>

#include "PluginBase.h"

class PluginCPU : public Plugin {
    private:
        unsigned long idleOld;
        unsigned long totalOld;
        ifstream fsStat;
    public:
        PluginCPU(std::string formatString);
        void update(void);
};

