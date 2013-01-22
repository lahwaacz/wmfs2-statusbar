#include "PluginDate.h"

PluginDate::PluginDate(void) {
    name = "PluginDate";
}

void PluginDate::update(void) {
    if (statusLine != NULL)
        free(statusLine);

    t = time(0);
    tm = localtime(&t);
    strftime(date, 128, "%a, %d %b %Y %T", tm);
  
    asprintf(&statusLine, formatDate, date);
}

