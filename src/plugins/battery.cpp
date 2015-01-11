#include <unistd.h>  // sleep

#include "battery.h"

using namespace std;

PluginBattery::PluginBattery(std::string formatString)
    : Plugin("battery", formatString)
{
    // TODO: config? (set defaults from main.cpp)
    timeout = 30;
    timeoutOffset = 3;

    fsState.open(config.battery_path_state.c_str());
    fsFull.open(config.battery_path_full.c_str());
    fsNow.open(config.battery_path_now.c_str());
}

void PluginBattery::update(void) {
    string state;
    int full = 0;
    int now = 0;

    if (fsState.fail() || fsFull.fail() || fsNow.fail())
        throw "unable to read ACPI battery events";

    // rewind to the beginning of the file
    fsState.seekg(0, ios::beg);
    fsFull.seekg(0, ios::beg);
    fsNow.seekg(0, ios::beg);

    // read values
    fsState >> state;
    fsFull >> full;
    fsNow >> now;
  
    int percent = full == 0 ? -1 : 100 * now / full;

    if (state == "Discharging" and percent >= 0 and percent <= config.battery_critical_percent) {
        if (! config.battery_critical_action1.empty()) {
            std::system(config.battery_critical_action1.c_str());
            if (! config.battery_critical_action2.empty()) {
                sleep(config.battery_critical_timeout);
                std::system(config.battery_critical_action2.c_str());
            }
        }
    }

    statusLine = fmt::format(formatString, state, percent);
}
