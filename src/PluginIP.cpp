#include "PluginIP.h"

PluginIP::PluginIP(void) {
    name = "PluginIP";

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        failed = true;
}

PluginIP::~PluginIP(void) {
    close(sockfd);
}

void PluginIP::update(void) {
    // first cleanup and init statusLine
    free(statusLine);
    statusLine = NULL;

    if (failed)
        throw "unable to create socket";

    ifr = {};
    if (config.network_active_interface)
        strncpy(ifr.ifr_name, *(config.network_active_interface), IFNAMSIZ-1);
    else    // default to loopback
        strncpy(ifr.ifr_name, "lo", IFNAMSIZ-1);

    /* I want to get an IPv4 IP address */
    ifr.ifr_addr.sa_family = AF_INET;

    if (ioctl(sockfd, SIOCGIFADDR, &ifr) == -1) {
        throw "get IP address ioctl failed";
    } else {
        asprintf(&statusLine, config.ip_format.c_str(), inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    }
}
