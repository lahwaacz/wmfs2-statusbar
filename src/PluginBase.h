#pragma once

#include <cstdio>   /* for *printf() */
#include <cstdlib>  /* for free() */
#include <unistd.h> /* for close() */

/* this will be in config one day... */
static const char* formatBattery = "^s[left;#aabbaa;Bat ]^s[left;#dddddd;%.1s %d%%]";
static const char* formatCPU = "^s[left;#aabbaa;CPU ]^g[left;150;14;%d;100;#888888;#991111;cpu]";
static const char* formatDate = "^s[right;#dddddd;%s]";
static const char* formatEssid = "^s[left;#aabbaa;ESSID]^s[left;#dddddd; %s]";
static const char* formatIP = "^s[left;#aabbaa;IP]^s[left;#dddddd; %s]";
static const char* formatDown = "^s[left;#aabbaa;Down ]^g[left;100;14;%d;5000;#888888;#00af00;down]";
static const char* formatUp = "^s[left;#aabbaa;Up ]^g[left;100;14;%d;2500;#888888;#af0000;up]";
static const char* formatRAM = "^s[left;#aabbaa;RAM ]^p[left;100;8;0;%ld;%ld;#888888;#771144]";
static const char* formatVolume = "^s[left;#aabbaa;Vol ]^s[left;#dddddd;%d%%]";

static const char* eth0upPath = "/sys/class/net/eth0/statistics/tx_bytes";
static const char* eth0downPath = "/sys/class/net/eth0/statistics/rx_bytes";

static const char* batteryFullPath = "/sys/class/power_supply/BAT0/energy_full";
static const char* batteryNowPath = "/sys/class/power_supply/BAT0/energy_now";
static const char* batteryStatePath = "/sys/class/power_supply/BAT0/status";
static const int batteryCriticalPercent = 6;
static const char* batteryCriticalAction = "systemctl hibernate";


inline void readFileInt(unsigned long* var, const char* path) {
    FILE *f = fopen(path, "r");
    if (!f)
        throw 1;
    fscanf(f, "%lu", var);
    fclose(f);
}

inline void readFileStr(char* buffer, int size, const char* path) {
    FILE *f = fopen(path, "r");
    if (!f)
        throw 1;
    fgets(buffer, size, f);
    fclose(f);
}


class Plugin {
    protected:
        const char* name = "<no-name-plugin>";
        bool failed = false;
        unsigned int timeout = 1;
        unsigned int timeoutOffset = 0;
        char* statusLine = NULL;

    public:
        const char* getName(void) {return name;};
        unsigned int getTimeout(void) {return timeout;};
        void setTimeout(unsigned int timeout) {this->timeout = timeout;};
        unsigned int getTimeoutOffset(void) {return timeoutOffset;};
        void setTimeoutOffset(unsigned int offset) {this->timeoutOffset = offset;};
        char* getStatusLine(void) {return statusLine;};

        // main method - redefine in subclasses
        virtual void update(void) {};
};
