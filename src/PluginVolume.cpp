#include "PluginVolume.h"

PluginVolume::PluginVolume(void) {
    name = "PluginVolume";
}

PluginVolume::~PluginVolume(void) {
    disconnect();
}

void PluginVolume::update(void) {
    // first cleanup and init statusLine
    free(statusLine);
    statusLine = NULL;

    if (client == NULL)
        reconnect();

    Device device = client->get_default_sink();
    if (device.mute) {
        asprintf(&statusLine, config.volume_format.c_str(), "M");
    } else {
        asprintf(&statusLine, config.volume_format.c_str(), device.volume_percent);
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

