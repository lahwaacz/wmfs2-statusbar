#include "ConfigParser.h"

// init - set defaults
//Config::Config(void) {
//    // defaults - every plugin must specify default values here!
//    battery_format              = "^s[left;#1793d0;Bat ]^s[left;#dddddd;%.1s %d%%]";
//    battery_path_full           = "/sys/class/power_supply/BAT1/energy_full";
//    battery_path_now            = "/sys/class/power_supply/BAT1/energy_now";
//    battery_path_state          = "/sys/class/power_supply/BAT1/status";
//    battery_critical_percent    = 6;
//    battery_critical_action1    = "notify-send 'Battery level critical, will hibernate in 5 seconds...'";
//    battery_critical_timeout    = 5;
//    battery_critical_action2    = "systemctl hibernate";
//
//    cpu_format                  = "^s[left;#1793d0;CPU ]^g[left;150;14;%d;100;#333333;#3f42b0;cpu]";
//    date_format                 = "^s[right;#dddddd;%s]";
//    essid_format                = "^s[left;#1793d0;ESSID]^s[left;#dddddd; %s]";
//    ip_format                   = "^s[left;#1793d0;IP]^s[left;#dddddd; %s]";
//    mpd_format                  = "^s[right;#1793d0;MPD ]^s[right;#dddddd;%d:%02d / %d:%02d ]^P[right;100;6;3;%d;%d;#333333;#11ff11]^s[right;#dddddd; %s]";
//
//    network_format_wireless     = "^s[left;#1793d0;Down ]^g[left;100;14;%d;300;#333333;#1c9a34;down] ^s[left;#888888; - ] ^s[left;#1793d0;Up ]^g[left;100;14;%d;300;#333333;#bc1e1e;up]";
//    network_format_wired        = "^s[left;#1793d0;Down ]^g[left;100;14;%d;5000;#333333;#1c9a34;down] ^s[left;#888888; - ] ^s[left;#1793d0;Up ]^g[left;100;14;%d;5000;#333333;#bc1e1e;up]";
//    network_wired_interface     = "eth0";
//    network_wireless_interface  = "wlan0";
//
//    ram_format                  = "^s[left;#1793d0;RAM ]^p[left;100;8;0;%ld;%ld;#333333;#1d1e64]";
//    volume_format               = "^s[left;#1793d0;Vol ]^s[left;#dddddd;%d%%]";
//}

Config::Config(void) {
    // defaults - every plugin must specify default values here!
    battery_format              = "Bat {0} {1}%";
    battery_path_full           = "/sys/class/power_supply/BAT1/energy_full";
    battery_path_now            = "/sys/class/power_supply/BAT1/energy_now";
    battery_path_state          = "/sys/class/power_supply/BAT1/status";
    battery_critical_percent    = 6;
    battery_critical_action1    = "notify-send 'Battery level critical, will hibernate in 5 seconds...'";
    battery_critical_timeout    = 5;
    battery_critical_action2    = "systemctl hibernate";

    cpu_format                  = "CPU {0: 3.0f}%";
    date_format                 = "{0}";
    essid_format                = "ESSID {0}";
    ip_format                   = "IP {0}";
    mpd_format                  = "MPD {0}:{1:02d} / {2}:{3:02d} {4}";

// DEPRECATED
//    network_format_wireless     = "Down %d - Up %d";
//    network_format_wired        = "Down %d - Up %d";
//    network_wired_interface     = "eth0";
    network_wireless_interface  = "wlan0";

    ram_format                  = "RAM {0:.2f}/{1:.2f}";
    volume_format               = "Vol {0}%";
}

// parse config file, return true means OK
bool Config::parseFile(string path) {
    string errorMessage = "";       // additional error message
    picojson::value v;              // create json object

    ifstream infile(path.c_str());  // read config file as inputstream
    if (infile.fail()) {            // handle read errors
        errorMessage = "unable to read file";
    } else {
        infile >> v;                // push config content into json object
        if (infile.fail())          // handle parse errors
            errorMessage = picojson::get_last_error();
    }
    infile.close();

    if (errorMessage.empty()) {
        // parse json object
        if (v.is<picojson::object>()) {
            const picojson::object& o = v.get<picojson::object>();
            for (picojson::object::const_iterator i = o.begin(); i != o.end(); ++i) {
                try {
                    parsePair(i->first, i->second);
                } catch (const char *msg) {
                    errorMessage = msg;
                    break;
                }
            }
        } else {
            errorMessage = "input is not JSON object.";
        }
    }

    if (!errorMessage.empty()) {
        cerr << "Error parsing config file '" << path << "': ";
        cerr << errorMessage << endl;
        return false;
    } else
        return true;
}

// parse single key:value pair
void Config::parsePair(const string & key, const picojson::value & value) {
    if (key.compare("battery_format") == 0)
        battery_format = value.get<string>();
    else if (key.compare("battery_path_full") == 0)
        battery_path_full = value.get<string>();
    else if (key.compare("battery_path_now") == 0)
        battery_path_now = value.get<string>();
    else if (key.compare("battery_path_state") == 0)
        battery_path_state = value.get<string>();
    else if (key.compare("battery_critical_percent") == 0) {
        if (value.is<double>())
            battery_critical_percent = (int)value.get<double>();
        else
            throw "battery_critical_percent is not type <double>";
    }
    else if (key.compare("battery_critical_action1") == 0)
        battery_critical_action1 = value.get<string>();
    else if (key.compare("battery_critical_timeout") == 0) {
        if (value.is<double>())
            battery_critical_timeout = (int)value.get<double>();
        else
            throw "battery_critical_timeout is not type <double>";
    }
    else if (key.compare("battery_critical_action2") == 0)
        battery_critical_action2 = value.get<string>();

    else if (key.compare("cpu_format") == 0)
        cpu_format = value.get<string>();
    else if (key.compare("date_format") == 0)
        date_format = value.get<string>();
    else if (key.compare("essid_format") == 0)
        essid_format = value.get<string>();
    else if (key.compare("ip_format") == 0)
        ip_format = value.get<string>();
    else if (key.compare("mpd_format") == 0)
        mpd_format = value.get<string>();

// DEPRECATED
//    else if (key.compare("network_format_wireless") == 0)
//        network_format_wireless = value.get<string>();
//    else if (key.compare("network_format_wired") == 0)
//        network_format_wired = value.get<string>();
//    else if (key.compare("network_wireless_interface") == 0)
//        network_wireless_interface = value.get<string>();
//    else if (key.compare("ram_format") == 0)
//        ram_format = value.get<string>();
//    else if (key.compare("volume_format") == 0)
//        volume_format = value.get<string>();
}

#ifdef DEBUG
// macro to show variable name and value
#define SHOW(a) std::cout << #a << ": " << (a) << std::endl

// print config values into cout
void Config::print(void) {
    cout << "Debug: config values dump" << endl;

    SHOW (battery_format);
    SHOW (battery_path_full);
    SHOW (battery_path_now);
    SHOW (battery_path_state);
    SHOW (battery_critical_percent);
    SHOW (battery_critical_action1);
    SHOW (battery_critical_timeout);
    SHOW (battery_critical_action2);

    SHOW (cpu_format);
    SHOW (date_format);
    SHOW (essid_format);
    SHOW (ip_format);
    SHOW (mpd_format);

// DEPRECATED
//    SHOW (network_format_wireless);
//    SHOW (network_format_wired);
//    SHOW (network_wireless_interface);
//    SHOW (network_wired_interface);

    SHOW (ram_format);
    SHOW (volume_format);
}
#endif // DEBUG
