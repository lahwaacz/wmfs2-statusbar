#include "PluginNetwork.h"

PluginNetwork::PluginNetwork(void) {
    name = "PluginNetwork";
    downOld = 0;
    upOld = 0;

    // format for up and down graphs
    format = config.get("network_format").c_str();

    // init wireless interface paths
    wireless.name = config.get("network_wireless_interface").c_str();
    asprintf(&wireless.pathDown, "/sys/class/net/%s/statistics/rx_bytes", wireless.name);
    asprintf(&wireless.pathUp, "/sys/class/net/%s/statistics/tx_bytes", wireless.name);
    asprintf(&wireless.pathState, "/sys/class/net/%s/operstate", wireless.name);

    // init wired interface paths
    wired.name = config.get("network_wired_interface").c_str();
    asprintf(&wired.pathDown, "/sys/class/net/%s/statistics/rx_bytes", wired.name);
    asprintf(&wired.pathUp, "/sys/class/net/%s/statistics/tx_bytes", wired.name);
    asprintf(&wired.pathState, "/sys/class/net/%s/operstate", wired.name);
}

void PluginNetwork::setActiveInterface(void) {
    char operstate[8];

    readFileStr(operstate, 8, wireless.pathState);
    if (std::strncmp(operstate, "up", 2) == 0) {
        config.set("network_active_interface", wireless.name);
        active = &wireless;
        return;
    }

    readFileStr(operstate, 8, wired.pathState);
    if (std::strncmp(operstate, "up", 2) == 0) {
        config.set("network_active_interface", wired.name);
        active = &wired;
        return;
    }

    config.set("network_active_interface", "lo");
}

void PluginNetwork::update(void) {
    if (statusLine != NULL) {
        free(statusLine);
        statusLine = NULL;
    }

    this->setActiveInterface();

    unsigned long down = getDown();
    unsigned long up = getUp();
    asprintf(&statusLine, format, down, up);
}

unsigned long PluginNetwork::getDown(void) {
    unsigned long down = 0;
    readFileInt(&down, active->pathDown);
    down /= 1024;
    unsigned long speed = 0;

    if (downOld != 0) speed = down - downOld;
    downOld = down;

    return speed;
}

unsigned long PluginNetwork::getUp(void) {
    unsigned long up = 0;
    readFileInt(&up, active->pathUp);
    up /= 1024;
    unsigned long speed = 0;

    if (upOld != 0) speed = up - upOld;
    upOld = up;
  
    return speed;
}

