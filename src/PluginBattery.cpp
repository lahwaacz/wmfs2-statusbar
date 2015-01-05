#include <unistd.h>  // sleep

#include <fstream>

#include "PluginBattery.h"

using namespace std;

PluginBattery::PluginBattery(std::string formatString)
    : Plugin("battery", formatString)
{
    timeout = 30;
    timeoutOffset = 3;

    pathFull = config.battery_path_full.c_str();
    pathNow = config.battery_path_now.c_str();
    pathState = config.battery_path_state.c_str();
}

void PluginBattery::update(void) {
    castValueFromFile(pathFull, full);
    castValueFromFile(pathNow, now);

    string state;
    ifstream fs(pathState);
    fs >> state;
  
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
