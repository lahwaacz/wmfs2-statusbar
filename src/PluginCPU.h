#pragma once

#include "PluginBase.h"

class PluginCPU : public Plugin {
    private:
        unsigned long idleOld;
        unsigned long totalOld;
    public:
        PluginCPU(std::string formatString);
        void update(void);
};

