#include "PluginNetwork.h"

PluginNetwork::PluginNetwork(void) {
    name = "PluginNetwork";
    downOld = 0;
    upOld = 0;

    // init wireless interface paths
    wireless.name = config.network_wireless_interface.c_str();
    wireless.format = config.network_format_wireless.c_str();
    asprintf(&wireless.pathDown, "/sys/class/net/%s/statistics/rx_bytes", wireless.name);
    asprintf(&wireless.pathUp, "/sys/class/net/%s/statistics/tx_bytes", wireless.name);
    asprintf(&wireless.pathCarrier, "/sys/class/net/%s/carrier", wireless.name);

    // init wired interface paths
    wired.name = config.network_wired_interface.c_str();
    wired.format = config.network_format_wired.c_str();
    asprintf(&wired.pathDown, "/sys/class/net/%s/statistics/rx_bytes", wired.name);
    asprintf(&wired.pathUp, "/sys/class/net/%s/statistics/tx_bytes", wired.name);
    asprintf(&wired.pathCarrier, "/sys/class/net/%s/carrier", wired.name);
}

void PluginNetwork::setActiveInterface(void) {
    int carrier = 0;

    readFileInt(&carrier, wireless.pathCarrier);
    if (carrier != 0) {
        config.network_active_interface = &wireless.name;
        active = &wireless;
        return;
    }

    readFileInt(&carrier, wired.pathCarrier);
    if (carrier != 0) {
        config.network_active_interface = &wired.name;
        active = &wired;
        return;
    }

    config.network_active_interface = NULL;
    active = NULL;
}

void PluginNetwork::update(void) {
    if (statusLine != NULL) {
        free(statusLine);
        statusLine = NULL;
    }

    this->setActiveInterface();

    unsigned long down = 0;
    unsigned long up = 0;
    if (active) {
        down = getDown();
        up = getUp();
        asprintf(&statusLine, active->format, down, up);
    } else {
        // some hardcoded format, doesn't matter because down and up are 0, but active is NULL
        asprintf(&statusLine, wired.format, down, up);
    }
}

unsigned long PluginNetwork::getDown(void) {
    unsigned long down = 0;
    readFileUnsignedLong(&down, active->pathDown);
    down /= 1024;
    unsigned long speed = 0;

    if (downOld != 0) speed = down - downOld;
    downOld = down;

    return speed;
}

unsigned long PluginNetwork::getUp(void) {
    unsigned long up = 0;
    readFileUnsignedLong(&up, active->pathUp);
    up /= 1024;
    unsigned long speed = 0;

    if (upOld != 0) speed = up - upOld;
    upOld = up;
  
    return speed;
}

