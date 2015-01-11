#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/wireless.h>
#include <unistd.h>  // close

#include <cstring>  // strncpy

#include "essid.h"

PluginEssid::PluginEssid(std::string formatString)
    : Plugin("essid", formatString)
{
    wirelessName = config.network_wireless_interface.c_str();

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        failed = true;
}

PluginEssid::~PluginEssid(void) {
    close(sockfd);
}

void PluginEssid::update(void) {
    if (failed)
        throw "unable to create socket";

    iwreq wreq = iwreq();
    strncpy(wreq.ifr_name, wirelessName, IFNAMSIZ-1);

    char buffer[IW_ESSID_MAX_SIZE] = {0};
    wreq.u.essid.pointer = buffer;
    wreq.u.essid.length = IW_ESSID_MAX_SIZE;

    if (ioctl(sockfd, SIOCGIWESSID, &wreq) == -1) {
        throw "get ESSID ioctl failed";
    }

    statusLine = fmt::format(formatString, buffer);
}
