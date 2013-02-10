#pragma once

#include "PluginBase.h"

struct NetworkInterface {
    const char* name;
    char* pathDown = NULL;
    char* pathUp = NULL;
    char* pathState = NULL;
    
    // Destructor
    ~NetworkInterface() {
        if (pathDown)
            free(pathDown);
        if (pathUp)
            free(pathUp);
        if (pathState)
            free(pathState);
    }
};

class PluginNetwork : public Plugin {
    private:
        unsigned long downOld;
        unsigned long upOld;
        NetworkInterface wireless;
        NetworkInterface wired;
        NetworkInterface* active = NULL;

    public:
        PluginNetwork(void);
        void setActiveInterface(void);
        void update(void);
        unsigned long getDown(void);
        unsigned long getUp(void);
};

