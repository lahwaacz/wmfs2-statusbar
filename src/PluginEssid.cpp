#include <string.h> /* for strncpy */

#include "PluginEssid.h"

PluginEssid::PluginEssid(void) {
    name = "PluginEssid";
    timeout = 30;
    timeoutOffset = 1;
    format = config.get("essid_format").c_str();
    wirelessName = config.get("network_wireless_interface").c_str();
    wiredName = config.get("network_wired_interface").c_str();

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        failed = true;
}

PluginEssid::~PluginEssid(void) {
    close(sockfd);
}

void PluginEssid::update(void) {
    if (statusLine != NULL)
        free(statusLine);

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
            asprintf(&statusLine, format, buffer);
        }

        // check if connected, set active network interface
        if (std::strncmp(buffer, "", 1) == 0)
            config.set("network_active_interface", wiredName);
        else
            config.set("network_active_interface", wirelessName);
    }
}
