#include <cstdlib>      // exit
#include <unistd.h>     // getopt
#include <sys/time.h>   // gettimeofday
#include <time.h>       // nanosleep

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
#include "PluginRAM.h"
#include "PluginVolume.h"


Config config = Config();       // global to share between plugins

// holds parsed command line options
const char *configPath = NULL;     /* -c option */

static const char *optString = "hc:";


static void usage(void) {
    std::cout << "usage: " << program_invocation_short_name << "[-c <path-to-config-file>]" << std::endl;
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

void updatePlugin(Plugin & plugin) {
    try {
        plugin.update();
    } catch (const char *msg) {
        std::cerr << "Failed to update plugin '" << plugin.getName() << "': ";
        std::cerr << msg << std::endl;
    } catch (fmt::FormatError & e) {
        std::cerr << "Formatting for plugin '" << plugin.getName() << "' failed: " << e.what() << std::endl;
    }
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

    std::vector<std::string> pluginNames = {"mpd", "ram", "cpu", "essid", "ipaddr", "battery", "volume", "date"};
    std::vector<Plugin*> plugins;

    for (std::vector<std::string>::iterator it = pluginNames.begin();
         it < pluginNames.end();
         it++)
    {
        std::string name = *it;
        Plugin* plugin = nullptr;

        if (name == "battery")
            plugin = new PluginBattery(config.battery_format);
        else if (name == "cpu")
            plugin = new PluginCPU(config.cpu_format);
        else if (name == "date")
            plugin = new PluginDate(config.date_format);
        else if (name == "essid")
            plugin = new PluginEssid(config.essid_format);
        else if (name == "ipaddr")
            plugin = new PluginIP(config.ip_format);
        else if (name == "mpd")
            plugin = new PluginMPD(config.mpd_format);
        else if (name == "ram")
            plugin = new PluginRAM(config.ram_format);
        else if (name == "volume")
            plugin = new PluginVolume(config.volume_format);

        plugins.push_back(plugin);
    }

    for (unsigned int i = 0; i < plugins.size(); i++) {
        // make sure all plugins are updated at the start (they are not updated
        // in the first mainloop iteration iff offset > 0)
        updatePlugin(*plugins[i]);
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

    // TODO: config
    int interval = 1;

    std::string statusLine;
    int counter = 0;
    struct timeval epoch;
    struct timespec timeoutSpec;
    while (counter < 1000) {
        statusLine = "";
        for (unsigned int i = 0; i < plugins.size(); i++) {
            if (i > 0)
                statusLine += RIGHT_SEP;

            if (counter % plugins[i]->getTimeout() == plugins[i]->getTimeoutOffset()) {
                updatePlugin(*plugins[i]);
            }
            if (plugins[i]->isFailed()) {
                // TODO: config
                statusLine += "^s[right;#ff0000;Plugin '";
                statusLine += plugins[i]->getName();
                statusLine += "' failed.]";
            } else {
                statusLine += plugins[i]->getStatusLine();
            }
        }
        std::cout << statusLine << std::endl;
        std::cout.flush();
//        xstatus.sendStatus(statusLine);
        counter++;

        // Provide updates on every full second (epoch time divisible by interval, e.g.
        // with interval == 60 we update at :00), which is as good as possible.
        // To do this we sleep until the next second (with microsecond precision) plus
        // (interval - 1 - modulo_alignment) seconds.
        gettimeofday(&epoch, NULL);
        timeoutSpec.tv_sec = interval - 1 - (epoch.tv_sec % interval);
        timeoutSpec.tv_nsec = (1e6 - epoch.tv_usec) * 1000;
        nanosleep(&timeoutSpec, NULL);
    }
}
