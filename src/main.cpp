#include <unistd.h> /* for sleep() */
#include <signal.h> /* signal handler */
#include <cstdlib>  /* for exit() */

#include <iostream>
#include <string>
#include <vector>

#include "Xstatus.h"

// plugins
#include "PluginBattery.h"
#include "PluginCPU.h"
#include "PluginDate.h"
#include "PluginEssid.h"
#include "PluginIP.h"
#include "PluginMPD.h"
#include "PluginNetwork.h"
#include "PluginRAM.h"
#include "PluginVolume.h"

#ifdef DEBUG
#include "debug.h"
#endif // DEBUG

#define LEFT_SEP "^s[left;#898989; - ]"
#define RIGHT_SEP "^s[right;#898989; - ]"

static Xstatus* xstatus;    // must be global so that signal handler can access it

void signalHandler(int signum) {
    if (signum == SIGTERM or signum == SIGINT) {
        delete xstatus;
        exit(signum);
    }
}

int main(int argc, char **argv) {
    std::string statusLine;
    xstatus = new Xstatus();

    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    Plugin* bat = new PluginBattery();
    Plugin* cpu = new PluginCPU();
    Plugin* date = new PluginDate();
    Plugin* essid = new PluginEssid();
    Plugin* ip = new PluginIP();
    Plugin* mpd = new PluginMPD();
    Plugin* net = new PluginNetwork();
    Plugin* ram = new PluginRAM();
    Plugin* vol = new PluginVolume();

    std::vector<Plugin*> plugins = {ram, cpu, net, mpd, essid, ip, bat, vol, date};

    // at the start update every plugin
    for (int i = 0; i < plugins.size(); i++) {
        plugins[i]->update();

        // check if timeout and timeoutOffset are sane
        int timeout = plugins[i]->getTimeout();
        int offset = plugins[i]->getTimeoutOffset();
        if (timeout < 1) {
            std::cout << plugins[i]->getName() << ": timeout is too low, setting to 1sec" << std::endl;
            plugins[i]->setTimeout(1);
        }
        if (offset < 0) {
            std::cout << plugins[i]->getName() << ": timeoutOffset is too low, setting to 0sec" << std::endl;
            plugins[i]->setTimeoutOffset(0);
        } else if (offset >= timeout) {
            std::cout << plugins[i]->getName() << ": timeoutOffset is too high, setting to (timeout-1)sec" << std::endl;
            plugins[i]->setTimeoutOffset(timeout-1);
        }
    }

    int counter = 0;
    for (;;) {
        sleep(1);
        #ifdef DEBUG
        std::cout << std::endl;
        #endif // DEBUG
        #ifdef WITH_BOOST
        boost::timer::auto_cpu_timer t;
        #endif // WITH_BOOST

        statusLine = "default ";
        for (int i = 0; i < plugins.size(); i++) {
            statusLine += LEFT_SEP;

            if (counter % plugins[i]->getTimeout() == plugins[i]->getTimeoutOffset()) {
                #ifdef DEBUG
                std::cout << "Updating " << plugins[i]->getName() << "\t";
                #endif // DEBUG
                #ifdef WITH_BOOST
                boost::timer::auto_cpu_timer t;
                #endif // WITH_BOOST

                try {
                    plugins[i]->update();
                    statusLine += plugins[i]->getStatusLine();
                } catch (...) {
                    statusLine += "^s[left;#ff0000;Plugin '";
                    statusLine += plugins[i]->getName();
                    statusLine += "' failed.]";
                }
            } else {
                statusLine += plugins[i]->getStatusLine();
            }
        }
        xstatus->sendStatus(statusLine);
        counter++;

        #ifdef DEBUG
        std::cout << "Total:\t\t\t";
        #endif // DEBUG
    }
    
    delete xstatus;
}
