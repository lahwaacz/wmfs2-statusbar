#include <string.h> /* for strncpy */

#include "PluginEssid.h"

PluginEssid::PluginEssid(void) {
    name = "PluginEssid";
    timeout = 10;
    timeoutOffset = 1;
    wirelessName = config.network_wireless_interface.c_str();

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        failed = true;
}

PluginEssid::~PluginEssid(void) {
    close(sockfd);
}

void PluginEssid::update(void) {
    if (statusLine != NULL) {
        free(statusLine);
        statusLine = NULL;
    }

    if (failed)
        throw 1;
    else {
        wreq = {};
        strncpy(wreq.ifr_name, wirelessName, IFNAMSIZ-1);
        
        char buffer[IW_ESSID_MAX_SIZE] = {0};
        wreq.u.essid.pointer = buffer;
        wreq.u.essid.length = IW_ESSID_MAX_SIZE;

        if (ioctl(sockfd, SIOCGIWESSID, &wreq) == -1) {
            throw 1;
//            log("Get ESSID ioctl failed");
        } else {
            asprintf(&statusLine, config.essid_format.c_str(), buffer);
        }
    }
}
