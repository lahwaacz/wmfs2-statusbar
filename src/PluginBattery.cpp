#include "PluginBattery.h"

PluginBattery::PluginBattery(void) {
    name = "PluginBattery";
    timeout = 30;
    timeoutOffset = 3;
}

void PluginBattery::update(void) {
    if (statusLine != NULL)
        free(statusLine);

    readFileInt(&full, batteryFullPath);
    readFileInt(&now, batteryNowPath);
    char state[16];
    readFileStr(state, 16, batteryStatePath);
  
    int percent = full == 0 ? -1 : 100 * now / full;

    if (std::strncmp(state, "Discharging", 2) == 0 and percent >= 0 and percent <= batteryCriticalPercent) {
        std::system("twmnc --aot -t 'Battery level critical' -c 'action in 5 seconds...'");
        sleep(5);
        std::system(batteryCriticalAction);
    }

    asprintf(&statusLine, formatBattery, state, percent);
}
