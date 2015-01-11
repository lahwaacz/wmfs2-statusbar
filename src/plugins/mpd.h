#pragma once

#include <mpd/client.h>

#include "plugin.h"

class PluginMPD : public Plugin {
    private:
        // TODO: password authentication
        // TODO: these should be configurable
        int connect_port = 0;
        int connect_timeout = 10000;
        // TODO: NULL is allowed here, which will respect MPD_HOST environment variable
        const char *connect_hostname = "localhost";

        struct mpd_connection *connection;
        struct mpd_song *song;
        struct mpd_status *status;
    public:
        PluginMPD(std::string formatString);
        ~PluginMPD(void);
        void update(void);
        bool connect(void);
        void disconnect(void);
        bool reconnect(void);
};

