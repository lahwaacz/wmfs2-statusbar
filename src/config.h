#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "picojson/picojson.h"

// TODO: move this into Config class
//#define LEFT_SEP "^s[left;#888888; - ]"
//#define RIGHT_SEP "^s[right;#888888; - ]"
#define LEFT_SEP " | "
#define RIGHT_SEP " | "


class Config {
    public:
        Config(void);
        void setDefaults(void);
        bool parseFile(std::string path);
        void parsePair(const std::string & key, const picojson::value & value);

        // automatically changes between wired and wireless, not configurable
        const char **network_active_interface = NULL;

        // configurable properties
        std::string battery_format;
        std::string battery_path_full;
        std::string battery_path_now;
        std::string battery_path_state;
        int battery_critical_percent;
        std::string battery_critical_action1;
        int battery_critical_timeout;
        std::string battery_critical_action2;

        std::string cpu_format;
        std::string date_format;
        std::string essid_format;
        std::string ip_format;
        std::string mpd_format;

        std::string network_format_wireless;
        std::string network_format_wired;
        std::string network_wireless_interface;
        std::string network_wired_interface;

        std::string ram_format;
        std::string volume_format;

        // debug only
        #ifdef DEBUG
        void print(void);
        #endif // DEBUG
};
