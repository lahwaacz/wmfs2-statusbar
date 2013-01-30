#include "PluginBattery.h"

PluginBattery::PluginBattery(void) {
    name = "PluginBattery";
    timeout = 30;
    timeoutOffset = 3;

    format = config.get("battery_format").c_str();
    pathFull = config.get("battery_path_full").c_str();
    pathNow = config.get("battery_path_now").c_str();
    pathState = config.get("battery_path_state").c_str();
    istringstream(config.get("battery_critical_percent")) >> criticalPercent;
    criticalAction = config.get("battery_critical_action").c_str();
}

void PluginBattery::update(void) {
    if (statusLine != NULL)
        free(statusLine);

    readFileInt(&full, pathFull);
    readFileInt(&now, pathNow);
    char state[16];
    readFileStr(state, 16, pathState);
  
    int percent = full == 0 ? -1 : 100 * now / full;

    if (std::strncmp(state, "Discharging", 2) == 0 and percent >= 0 and percent <= criticalPercent) {
        std::system(config.get("battery_critical_action1").c_str());
        int timeout;
        istringstream(config.get("battery_critical_timeout")) >> timeout;
        sleep(timeout);
        std::system(config.get("battery_critical_action2").c_str());
    }

    asprintf(&statusLine, format, state, percent);
}
