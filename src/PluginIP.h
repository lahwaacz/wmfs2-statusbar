#pragma once

#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/if.h>
#include <arpa/inet.h>

#include "PluginBase.h"

class PluginIP : public Plugin {
    private:
        int sockfd;
        struct ifreq ifr = {};

    public:
        PluginIP(void);
        ~PluginIP(void);
        void update(void);
};

