#include "PluginDate.h"

PluginDate::PluginDate(void) {
    name = "PluginDate";
}

void PluginDate::update(void) {
    // first cleanup and init statusLine
    free(statusLine);
    statusLine = NULL;

    t = time(0);
    tm = localtime(&t);
    strftime(date, 128, "%a, %d %b %Y %T", tm);
  
    asprintf(&statusLine, config.date_format.c_str(), date);
}

