#include "PluginNetwork.h"

PluginNetwork::PluginNetwork(void) {
    name = "PluginNetwork";
    downOld = 0;
    upOld = 0;
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
    readFileInt(&down, eth0downPath);
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
    readFileInt(&up, eth0upPath);
    up /= 1024;
    unsigned long speed = 0;

    if (upOld != 0) speed = up - upOld;
    upOld = up;
  
    char* ret;
    asprintf(&ret, formatUp, speed);
  
    return ret;
}

