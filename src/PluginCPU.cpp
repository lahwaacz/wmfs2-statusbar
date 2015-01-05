#include <cstdio>   // fscanf

#include "PluginCPU.h"

PluginCPU::PluginCPU(std::string formatString)
    : Plugin("cpu", formatString)
{
    idleOld = 0;
    totalOld = 0;
}

void PluginCPU::update(void) {
    unsigned long active[3];
    unsigned long idle;
    unsigned long total;
    double percent;

    FILE *f = fopen("/proc/stat", "r");
  
    if (!f)
        throw "unable to read /proc/stat";
  
    fscanf(f, "%*s %lu %lu %lu %lu", &active[0], &active[1], &active[2], &idle);
    fclose(f);
  
    total = active[0] + active[1] + active[2] + idle;
    percent = 100 * ((double)(total - idle - (totalOld - idleOld)) / (double)(total - totalOld));

    totalOld = total;
    idleOld = idle;
  
    statusLine = fmt::format(formatString, percent);
}

