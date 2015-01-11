#include "date.h"

PluginDate::PluginDate(std::string formatString)
    : Plugin("date", formatString)
{
}

void PluginDate::update(void) {
    t = time(0);
    tm = localtime(&t);
    // TODO: format should be configurable
    strftime(date, 128, "%a, %d %b %Y %T", tm);
  
    statusLine = fmt::format(formatString, date);
}

