#pragma once

#include <pamixer/pulseaudio.hh>
#include <pamixer/device.hh>

#include "plugin.h"

class PluginVolume : public Plugin {
    private:
        Pulseaudio* client = NULL;

    public:
        PluginVolume(std::string formatString);
        ~PluginVolume(void);
        void update(void);
        void connect(void);
        void disconnect(void);
        void reconnect(void);
};

