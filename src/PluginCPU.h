#pragma once

#include "PluginBase.h"

class PluginCPU : public Plugin {
    private:
        unsigned long idleOld;
        unsigned long totalOld;
    public:
        PluginCPU(void);
        void update(void);
};

