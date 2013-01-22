#pragma once

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/wireless.h>

#include "PluginBase.h"

class PluginEssid : public Plugin {
    private:
        int sockfd;
        struct iwreq wreq = {};

    public:
        PluginEssid(void);
        ~PluginEssid(void);
        void update(void);
};

