#include <limits>

#include "ram.h"

using namespace std;

PluginRAM::PluginRAM(std::string formatString)
    : Plugin("ram", formatString)
{
    meminfo.open("/proc/meminfo");
    // factor for KiB -> GiB conversion (1024 * 1024)
    unitFactor = 1048576;
}

void PluginRAM::update(void) {
    long total = 0;
    long used = 0;

    // reset stream to the beginning of file
    meminfo.seekg(0, ios::beg);

    if (meminfo.fail())
        throw "unable to read /proc/meminfo";

    string desc;
    long value;
    int readCount = 0;

    // parse meminfo file, relevant values are:
    //   total = MemTotal
    //    used = MemTotal - MemFree - Buffers - Cached
    while (meminfo.good()) {
        // extract description (first column) and value (second column)
        meminfo >> desc >> value;
        // ignore the rest of this line
        meminfo.ignore(numeric_limits<streamsize>::max(), '\n');

        if (desc == "MemTotal:") {
            total = value;
            used += value;
            readCount++;
        }
        else if (desc == "MemFree:" || desc == "Buffers:" || desc == "Cached:") {
            used -= value;
            readCount++;
        }

        // skip the rest of the file when we have what we need
        if (readCount == 4)
            break;
    }

    statusLine = fmt::format(formatString, (float) used / unitFactor, (float) total / unitFactor);
}

