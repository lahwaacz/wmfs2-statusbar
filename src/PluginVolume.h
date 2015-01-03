#pragma once

#include <cstdio>

#include "PluginBase.h"

#include "pamixer/pulseaudio.hh"
#include "pamixer/device.hh"

class PluginVolume : public Plugin {
    private:
        Pulseaudio* client = NULL;

    public:
        PluginVolume(void);
        ~PluginVolume(void);
        void update(void);
        void connect(void);
        void disconnect(void);
        void reconnect(void);
};

