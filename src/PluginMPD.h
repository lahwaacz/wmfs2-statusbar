#pragma once

#include <mpd/client.h>

#include "PluginBase.h"

class PluginMPD : public Plugin {
    private:
        int connect_port = 0;
        int connect_timeout = 10000;
        const char* connect_hostname = "localhost";

        struct mpd_connection* connection;
        struct mpd_song* song;
        struct mpd_status* status;
    public:
        PluginMPD(void);
        ~PluginMPD(void);
        void update(void);
        bool connect(void);
        void disconnect(void);
        bool reconnect(void);
};

