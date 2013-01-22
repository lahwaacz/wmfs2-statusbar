#pragma once

#include <cstdio>

#include "PluginBase.h"

/* lib is part of ponymix
 * https://github.com/falconindy/ponymix
 */
#include "pulse.h"

class PluginVolume : public Plugin {
    private:
        PulseClient* client = NULL;
        Device* device = NULL;
        ServerInfo defaults = {};

    public:
        PluginVolume(void);
        ~PluginVolume(void);
        void update(void);
        void connect(void);
        void disconnect(void);
        void reconnect(void);
};

