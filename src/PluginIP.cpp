#include <string.h> /* for strncpy */

#include "PluginIP.h"

PluginIP::PluginIP(void) {
    name = "PluginIP";
    timeout = 10;
    timeoutOffset = 2;
    format = config.get("ip_format").c_str();

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        failed = true;
}

PluginIP::~PluginIP(void) {
    close(sockfd);
}

void PluginIP::update(void) {
    if (statusLine != NULL) {
        free(statusLine);
        statusLine = NULL;
    }

    if (failed)
        throw 1;
    else {
        ifr = {};
        strncpy(ifr.ifr_name, config.get("network_active_interface").c_str(), IFNAMSIZ-1);

        /* I want to get an IPv4 IP address */
        ifr.ifr_addr.sa_family = AF_INET;

        if (ioctl(sockfd, SIOCGIFADDR, &ifr) == -1) {
            throw 1;
//            log("Get IP address ioctl failed");
        } else {
            asprintf(&statusLine, format, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
        }
    }
}
