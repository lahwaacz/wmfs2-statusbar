#include "PluginVolume.h"

PluginVolume::PluginVolume(void) {
    name = "PluginVolume";
    format = config.get("volume_format").c_str();
    connect();
}

PluginVolume::~PluginVolume(void) {
    disconnect();
}

void PluginVolume::update(void) {
    if (statusLine != NULL)
        free(statusLine);

    if (client == NULL)
        reconnect();

    client->populate_sinks();
    asprintf(&statusLine, format, device->Volume());
}

void PluginVolume::connect(void) {
    client = new PulseClient("wmfs-statusbar");
    client->Populate();
    defaults = client->GetDefaults();
    device = client->GetDevice(defaults.sink.c_str(), DEVTYPE_SINK);
}

void PluginVolume::disconnect(void) {
    delete client;
    client = NULL;
    device = NULL;
}

void PluginVolume::reconnect(void) {
    disconnect();
    connect();
}

