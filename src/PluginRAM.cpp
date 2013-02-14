#include "PluginRAM.h"

PluginRAM::PluginRAM(void) {
    name = "PluginRAM";
}

void PluginRAM::update(void) {
    if (statusLine != NULL) {
        free(statusLine);
        statusLine = NULL;
    }

    long total, mfree, buf, cache;
    FILE *f = fopen("/proc/meminfo", "r");
  
    if (!f)
        throw "unable to read /proc/meminfo";
  
    fscanf(f, "MemTotal: %ld kB\n"
              "MemFree:  %ld kB\n"
              "Buffers:  %ld kB\n"
              "Cached:   %ld kB\n", &total, &mfree, &buf, &cache);
    fclose(f);
    asprintf(&statusLine, config.ram_format.c_str(), (total - (mfree + buf + cache)), total);
}

