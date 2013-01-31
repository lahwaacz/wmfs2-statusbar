#include "PluginNetwork.h"

PluginNetwork::PluginNetwork(void) {
    name = "PluginNetwork";
    downOld = 0;
    upOld = 0;

    formatDown = config.get("network_format_down").c_str();
    formatUp = config.get("network_format_up").c_str();
    asprintf(&pathUp, "/sys/class/net/%s/statistics/tx_bytes", config.get("network_wireless_interface").c_str());
    asprintf(&pathDown, "/sys/class/net/%s/statistics/rx_bytes", config.get("network_wireless_interface").c_str());
}

PluginNetwork::~PluginNetwork(void) {
    free(pathUp);
    free(pathDown);
}

void PluginNetwork::update(void) {
    if (statusLine != NULL)
        free(statusLine);

    char* down = getDown();
    char* up = getUp();
    asprintf(&statusLine, "%s ^s[left;#898989; - ] %s", down, up);
    free(down);
    free(up);
}

char* PluginNetwork::getDown(void) {
    unsigned long down = 0;
    readFileInt(&down, pathDown);
    down /= 1024;
    unsigned long speed = 0;

    if (downOld != 0) speed = down - downOld;
    downOld = down;
  
    char* ret;
    asprintf(&ret, formatDown, speed);
  
    return ret;
}

char* PluginNetwork::getUp(void) {
    unsigned long up = 0;
    readFileInt(&up, pathUp);
    up /= 1024;
    unsigned long speed = 0;

    if (upOld != 0) speed = up - upOld;
    upOld = up;
  
    char* ret;
    asprintf(&ret, formatUp, speed);
  
    return ret;
}

