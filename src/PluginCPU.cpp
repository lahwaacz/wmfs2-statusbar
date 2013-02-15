#include "PluginCPU.h"

PluginCPU::PluginCPU(void) {
    name = "PluginCPU";
    idleOld = 0;
    totalOld = 0;
}

void PluginCPU::update(void) {
    // first cleanup and init statusLine
    free(statusLine);
    statusLine = NULL;

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
  
    asprintf(&statusLine, config.cpu_format.c_str(), (int)percent);
}

