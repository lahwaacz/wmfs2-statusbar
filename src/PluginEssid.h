#pragma once

#include "PluginBase.h"

class PluginEssid : public Plugin {
    private:
        int sockfd;
        const char *wirelessName;

    public:
        PluginEssid(std::string formatString);
        ~PluginEssid(void);
        void update(void);
};

