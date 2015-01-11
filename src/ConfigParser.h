#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "picojson/picojson.h"

using namespace std;

// TODO: move this into Config class
//#define LEFT_SEP "^s[left;#888888; - ]"
//#define RIGHT_SEP "^s[right;#888888; - ]"
#define LEFT_SEP " | "
#define RIGHT_SEP " | "


class Config {
    public:
        Config(void);
        void setDefaults(void);
        bool parseFile(string path);
        void parsePair(const string & key, const picojson::value & value);

        // automatically changes between wired and wireless, not configurable
        const char **network_active_interface = NULL;

        // configurable properties
        string battery_format;
        string battery_path_full;
        string battery_path_now;
        string battery_path_state;
        int battery_critical_percent;
        string battery_critical_action1;
        int battery_critical_timeout;
        string battery_critical_action2;

        string cpu_format;
        string date_format;
        string essid_format;
        string ip_format;
        string mpd_format;

        string network_format_wireless;
        string network_format_wired;
        string network_wireless_interface;
        string network_wired_interface;

        string ram_format;
        string volume_format;

        // debug only
        #ifdef DEBUG
        void print(void);
        #endif // DEBUG
};
