#include "PluginMPD.h"

PluginMPD::PluginMPD(void) {
    name = "PluginMPD";
    connection = NULL;
    song = NULL;
    status = NULL;
}

PluginMPD::~PluginMPD(void) {
    disconnect();
}

void PluginMPD::update(void) {
    // first cleanup and init statusLine
    free(statusLine);
    statusLine = NULL;

    // init variables
    int elapsedTime = 0;
    int totalTime = 0;
    int totalPulseBar = 100;    // workarround, setting 0/0 for pulse bar behaves badly
    char *songInfoText = NULL;

    if (!connect())
        throw "unable to connect to MPD daemon";

    status = mpd_run_status(connection);
    if (mpd_status_get_state(status) == MPD_STATE_PLAY or mpd_status_get_state(status) == MPD_STATE_PAUSE) {
        song = mpd_run_current_song(connection);

        elapsedTime = mpd_status_get_elapsed_time(status);
        totalTime = mpd_status_get_total_time(status);
        totalPulseBar = totalTime;
        
        asprintf(&songInfoText, "%.20s - %.30s", 
                 mpd_song_get_tag(song, MPD_TAG_ARTIST, 0),
                 mpd_song_get_tag(song, MPD_TAG_TITLE, 0));

        mpd_song_free(song);
    }

    asprintf(&statusLine, config.mpd_format.c_str(),
             elapsedTime / 60, elapsedTime % 60, totalTime / 60, totalTime % 60,
             elapsedTime, totalPulseBar, (songInfoText ? songInfoText : ""));

    // cleanup
    mpd_status_free(status);
    free(songInfoText);

    // until I find way to detect MPD restart...
    disconnect();
}

bool PluginMPD::connect(void) {
    connection = mpd_connection_new(connect_hostname, connect_port, connect_timeout);
    if (mpd_connection_get_error(connection) == MPD_ERROR_SUCCESS)
        return true;
    else {
        connection = NULL;
        return false;
    }
}

void PluginMPD::disconnect(void) {
    mpd_response_finish(connection);
    mpd_connection_free(connection);
    connection = NULL;
}

bool PluginMPD::reconnect(void) {
    disconnect();
    return connect();
}
