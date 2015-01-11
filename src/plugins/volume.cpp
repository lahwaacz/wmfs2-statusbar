#include "volume.h"

PluginVolume::PluginVolume(std::string formatString)
    : Plugin("volume", formatString)
{
}

PluginVolume::~PluginVolume(void) {
    disconnect();
}

void PluginVolume::update(void) {
    if (client == NULL)
        reconnect();

    Device device = client->get_default_sink();
    if (device.mute) {
        statusLine = fmt::format(formatString, "M");
    } else {
        statusLine = fmt::format(formatString, device.volume_percent);
    }
}

void PluginVolume::connect(void) {
    client = new Pulseaudio("wmfs-statusbar");
}

void PluginVolume::disconnect(void) {
    delete client;
    client = NULL;
}

void PluginVolume::reconnect(void) {
    disconnect();
    connect();
}

