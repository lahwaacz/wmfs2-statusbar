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
    if (statusLine != NULL)
        free(statusLine);

    int totalTime = 0;
    int elapsedTime = 0;

    if (!connect())
        return;
    status = mpd_run_status(connection);
    if (mpd_status_get_state(status) == MPD_STATE_PLAY or mpd_status_get_state(status) == MPD_STATE_PAUSE) {
        song = mpd_run_current_song(connection);

        totalTime = mpd_status_get_total_time(status);
        elapsedTime = mpd_status_get_elapsed_time(status);
        
        asprintf(&statusLine,
                    "^s[left;#aabbaa;MPD ]"
                    "^s[left;#dddddd;%d:%02d / %d:%02d ]"
                    "^P[left;100;6;3;%d;%d;#888888;#11ff11]"
                    "^s[left;#dddddd; %.20s - %.30s]",
                 elapsedTime / 60, elapsedTime % 60, totalTime / 60, totalTime % 60,
                 elapsedTime, totalTime,
                 mpd_song_get_tag(song, MPD_TAG_ARTIST, 0),
                 mpd_song_get_tag(song, MPD_TAG_TITLE, 0));
        mpd_song_free(song);
    } else {
        asprintf(&statusLine,
                    "^s[left;#aabbaa;MPD ]"
                    "^s[left;#dddddd;%d:%02d / %d:%02d ]"
                    "^P[left;100;6;3;%d;%d;#888888;#11ff11]",
                 0, 0, 0, 0,
                 1, 100);
    }
    mpd_status_free(status);

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
