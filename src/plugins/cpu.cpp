#include "cpu.h"

PluginCPU::PluginCPU(std::string formatString)
    : Plugin("cpu", formatString)
{
    idleOld = 0;
    totalOld = 0;
    fsStat.open("/proc/stat");
}

void PluginCPU::update(void) {
    unsigned long active[3];
    unsigned long idle;
    unsigned long total;
    float percent;

    if (fsStat.fail())
        throw "unable to read /proc/stat";

    fsStat.seekg(0, std::ios::beg);
  
    // ignore first column (assume <16 chars)
    fsStat.ignore(16, ' ');
    fsStat >> active[0] >> active[1] >> active[2] >> idle;
  
    total = active[0] + active[1] + active[2] + idle;
    percent = 100 * ((float)(total - idle - (totalOld - idleOld)) / (float)(total - totalOld));

    totalOld = total;
    idleOld = idle;
  
    statusLine = fmt::format(formatString, percent);
}

