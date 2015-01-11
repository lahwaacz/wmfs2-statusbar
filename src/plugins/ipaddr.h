#pragma once

#include "plugin.h"

class PluginIP : public Plugin {
    private:
        int sockfd;

    public:
        PluginIP(std::string formatString);
        ~PluginIP(void);
        void update(void);
};

