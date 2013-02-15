#include <unistd.h> /* for sleep(), getopt() */
#include <cstdlib>  /* for exit() */

#include <iostream>
#include <string>
#include <vector>

#include "Xstatus.h"
#include "ConfigParser.h"

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

#ifdef WITH_BOOST
#include <boost/timer/timer.hpp>
#endif // WITH_BOOST


Config config = Config();       // global to share between plugins

// holds parsed command line options
const char *configPath = NULL;     /* -c option */

static const char *optString = "hc:";


static void usage(void) {
    printf("usage: %s [-c <path-to-config-file>]\n", program_invocation_short_name);
    exit(EXIT_SUCCESS);
}

bool parseArgs(int argc, char **argv) {
    for (;;) {
        int opt = getopt(argc, argv, optString);
        if (opt == -1)
            break;

        switch (opt) {
            case 'c':
                configPath = optarg;
                break;
            case 'h':
                usage();
                break;
            default:
                return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    // parse command line arguments
    if (!parseArgs(argc, argv))
        return 1;

    // load config file if specified
    if (configPath)
        config.parseFile(configPath);

    #ifdef DEBUG
    config.print();     // dump config values
    #endif // DEBUG

    Xstatus xstatus = Xstatus();

    Plugin* bat = new PluginBattery();
    Plugin* cpu = new PluginCPU();
    Plugin* date = new PluginDate();
    Plugin* essid = new PluginEssid();
    Plugin* ip = new PluginIP();
    Plugin* mpd = new PluginMPD();
    Plugin* net = new PluginNetwork();
    Plugin* ram = new PluginRAM();
    Plugin* vol = new PluginVolume();

    std::vector<Plugin*> plugins = {mpd, ram, cpu, net, essid, ip, bat, vol, date};

    // at the start update every plugin
    for (unsigned int i = 0; i < plugins.size(); i++) {
        try {
            plugins[i]->update();
        } catch (const char *msg) {
            std::cerr << "Failed to update plugin '" << plugins[i]->getName() << "': ";
            std::cerr << msg << std::endl;
        }

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

    std::string statusLine;
    int counter = 0;
    for (;;) {
        sleep(1);
        #ifdef WITH_BOOST
        std::cout << std::endl;
        boost::timer::auto_cpu_timer t;
        #endif // WITH_BOOST

        statusLine = "default ";
        for (unsigned int i = 0; i < plugins.size(); i++) {
            statusLine += RIGHT_SEP;

            if (counter % plugins[i]->getTimeout() == plugins[i]->getTimeoutOffset()) {
                #ifdef WITH_BOOST
                std::cout << "Updating " << plugins[i]->getName() << "\t";
                boost::timer::auto_cpu_timer t;
                #endif // WITH_BOOST

                try {
                    plugins[i]->update();
                } catch (const char *msg) {
                    std::cerr << "Failed to update plugin '" << plugins[i]->getName() << "': ";
                    std::cerr << msg << std::endl;
                }
            }
            char *pluginStatus = plugins[i]->getStatusLine();
            if (pluginStatus == NULL) {
                statusLine += "^s[left;#ff0000;Plugin '";
                statusLine += plugins[i]->getName();
                statusLine += "' failed.]";
            } else {
                statusLine += pluginStatus;
            }
        }
        xstatus.sendStatus(statusLine);
        counter++;

        #ifdef WITH_BOOST
        std::cout << "Total:\t\t\t";
        #endif // WITH_BOOST
    }
}
