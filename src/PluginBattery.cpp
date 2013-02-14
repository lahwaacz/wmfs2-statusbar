#include "PluginBattery.h"

PluginBattery::PluginBattery(void) {
    name = "PluginBattery";
    timeout = 30;
    timeoutOffset = 3;

    pathFull = config.battery_path_full.c_str();
    pathNow = config.battery_path_now.c_str();
    pathState = config.battery_path_state.c_str();
    criticalPercent = config.battery_critical_percent;
}

void PluginBattery::update(void) {
    if (statusLine != NULL) {
        free(statusLine);
        statusLine = NULL;
    }

    readFileUnsignedLong(&full, pathFull);
    readFileUnsignedLong(&now, pathNow);
    char state[16];
    readFileStr(state, 16, pathState);
  
    int percent = full == 0 ? -1 : 100 * now / full;

    if (std::strncmp(state, "Discharging", 2) == 0 and percent >= 0 and percent <= criticalPercent) {
        if (! config.battery_critical_action1.empty()) {
            std::system(config.battery_critical_action1.c_str());
            if (! config.battery_critical_action2.empty()) {
                sleep(config.battery_critical_timeout);
                std::system(config.battery_critical_action2.c_str());
            }
        }
    }

    asprintf(&statusLine, config.battery_format.c_str(), state, percent);
}
