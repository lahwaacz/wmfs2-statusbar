#include "PluginCPU.h"

PluginCPU::PluginCPU(void) {
    name = "PluginCPU";
    idleOld = 0;
    totalOld = 0;
    format = config.get("cpu_format").c_str();
}

void PluginCPU::update(void) {
    if (statusLine != NULL)
        free(statusLine);

    unsigned long active[3];
    unsigned long idle;
    unsigned long total;
    double percent;

    FILE *f = fopen("/proc/stat", "r");
  
    if (!f)
        throw 1;
  
    fscanf(f, "%*s %lu %lu %lu %lu", &active[0], &active[1], &active[2], &idle);
    fclose(f);
  
    total = active[0] + active[1] + active[2] + idle;
    percent = 100 * ((double)(total - idle - (totalOld - idleOld)) / (double)(total - totalOld));

    totalOld = total;
    idleOld = idle;
  
    asprintf(&statusLine, format, (int)percent);
}

