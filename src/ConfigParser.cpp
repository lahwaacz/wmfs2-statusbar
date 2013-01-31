#include "ConfigParser.h"

//using namespace std;

// init - set defaults
Config::Config(void) {
    setDefaults();
};

// return value for key
string Config::get(string key) {
    return dict[key];
};

// defaults - every plugin must specify default values here!
void Config::setDefaults(void) {
    dict["battery_format"]              = "^s[left;#aabbaa;Bat ]^s[left;#dddddd;%.1s %d%%]";
    dict["battery_path_full"]           = "/sys/class/power_supply/BAT0/energy_full";
    dict["battery_path_now"]            = "/sys/class/power_supply/BAT0/energy_now";
    dict["battery_path_state"]          = "/sys/class/power_supply/BAT0/status";
    dict["battery_critical_percent"]    = "6";
    dict["battery_critical_action1"]    = "twmnc --aot -t 'Battery level critical' -c 'action in 5 seconds...'";
    dict["battery_critical_timeout"]    = "5";
    dict["battery_critical_action2"]    = "systemctl hibernate";

    dict["cpu_format"]                  = "^s[left;#aabbaa;CPU ]^g[left;150;14;%d;100;#888888;#991111;cpu]";
    dict["date_format"]                 = "^s[right;#dddddd;%s]";
    dict["essid_format"]                = "^s[left;#aabbaa;ESSID]^s[left;#dddddd; %s]";
    dict["ip_format"]                   = "^s[left;#aabbaa;IP]^s[left;#dddddd; %s]";
    dict["network_format_down"]         = "^s[left;#aabbaa;Down ]^g[left;100;14;%d;300;#888888;#00af00;down]";
    dict["network_format_up"]           = "^s[left;#aabbaa;Up ]^g[left;100;14;%d;300;#888888;#af0000;up]";
    dict["network_wired_interface"]     = "eth0";
    dict["network_wireless_interface"]  = "wlan0";
    dict["network_active_interface"]    = "";
    dict["ram_format"]                  = "^s[left;#aabbaa;RAM ]^p[left;100;8;0;%ld;%ld;#888888;#771144]";
    dict["volume_format"]               = "^s[left;#aabbaa;Vol ]^s[left;#dddddd;%d%%]";
}

// set 'key=value' pair; ignored if 'key' doesn't already exist
void Config::set(string key, string value) {
    if (dict.count(key) == 0) {
        cerr << "Ignoring invalid config key: " << key << endl;
    } else {
        dict[key] = value;
    }
}

// print config into specified ostream (default: cout)
void Config::print(ostream& stream) {
    for( t_dict::iterator ii=dict.begin(); ii!=dict.end(); ii++) {
        stream << "'" << (*ii).first << "' = '" << (*ii).second << "'" << endl;
    }
}

// parse config file
void Config::parseConfigFile(string path) {
    ifstream infile(path.c_str());
    if (infile.good()) {
        string line;
        while (getline(infile, line)) {
            istringstream is_line(line);
            trim(line);

            // ignore commented lines
            line = line.substr(0, line.find("#"));
            line = line.substr(0, line.find("//"));

            // ignore empty lines
            if (line.empty())
                continue;
 
            unsigned sep = line.find("=");
            string key = line.substr(0, sep);
            string value = line.substr(sep + 1);
            set(trim(key), trim(value));
        }
    } else {
        cerr << "Error opening config file: " << path << endl;
        throw 1;
    }
    infile.close();
}
