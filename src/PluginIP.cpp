#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <arpa/inet.h>
#include <unistd.h> // close

#include <cstring>  // strncpy

#include "PluginIP.h"

PluginIP::PluginIP(std::string formatString)
    : Plugin("ipaddr", formatString)
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        failed = true;
}

PluginIP::~PluginIP(void) {
    close(sockfd);
}

void PluginIP::update(void) {
    if (failed)
        throw "unable to create socket";

    ifreq ifr = ifreq();
    if (config.network_active_interface)
        strncpy(ifr.ifr_name, *(config.network_active_interface), IFNAMSIZ-1);
    else    // default to loopback
        strncpy(ifr.ifr_name, "lo", IFNAMSIZ-1);

    /* I want to get an IPv4 IP address */
    ifr.ifr_addr.sa_family = AF_INET;

    if (ioctl(sockfd, SIOCGIFADDR, &ifr) == -1) {
        throw "get IP address ioctl failed";
    }

    statusLine = fmt::format(formatString, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
}
