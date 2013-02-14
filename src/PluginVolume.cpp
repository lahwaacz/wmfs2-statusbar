#include "PluginVolume.h"

PluginVolume::PluginVolume(void) {
    name = "PluginVolume";
    connect();
}

PluginVolume::~PluginVolume(void) {
    disconnect();
}

void PluginVolume::update(void) {
    if (statusLine != NULL) {
        free(statusLine);
        statusLine = NULL;
    }

    if (client == NULL)
        reconnect();

    client->populate_sinks();
    asprintf(&statusLine, config.volume_format.c_str(), device->Volume());
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

