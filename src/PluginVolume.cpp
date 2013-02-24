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

    client->populate_sinks();
    if (device->Muted()) {
        asprintf(&statusLine, config.volume_format.c_str(), "M");
    } else {
        char *perc;
        asprintf(&perc, "%d%%", device->Volume());
        asprintf(&statusLine, config.volume_format.c_str(), perc);
        free(perc);
    }
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

