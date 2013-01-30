#pragma once

#include "PluginBase.h"

class PluginNetwork : public Plugin {
    private:
        unsigned long downOld;
        unsigned long upOld;
        const char* formatDown;
        const char* formatUp;
        char* pathDown;
        char* pathUp;
    public:
        PluginNetwork(void);
        ~PluginNetwork(void);
        void update(void);
        char* getDown(void);
        char* getUp(void);
};

