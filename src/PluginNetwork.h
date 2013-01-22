#pragma once

#include "PluginBase.h"

class PluginNetwork : public Plugin {
    private:
        unsigned long downOld;
        unsigned long upOld;
    public:
        PluginNetwork(void);
        void update(void);
        char* getDown(void);
        char* getUp(void);
};

