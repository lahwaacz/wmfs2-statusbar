#include "PluginRAM.h"

PluginRAM::PluginRAM(void) {
    name = "PluginRAM";
}

void PluginRAM::update(void) {
    if (statusLine != NULL)
        free(statusLine);

    long total, mfree, buf, cache;
    FILE *f = fopen("/proc/meminfo", "r");
  
    if (!f)
        throw 1;
  
    fscanf(f, "MemTotal: %ld kB\n"
              "MemFree:  %ld kB\n"
              "Buffers:  %ld kB\n"
              "Cached:   %ld kB\n", &total, &mfree, &buf, &cache);
    fclose(f);
    asprintf(&statusLine, formatRAM, (total - (mfree + buf + cache)), total);
}

