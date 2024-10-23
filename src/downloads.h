#ifndef BEST403UNLOCKER_DOWNLOADS_H_
#define BEST403UNLOCKER_DOWNLOADS_H_

#include <string>

struct DnsResult {
  std::string dns;
  size_t downloaded;
};

DnsResult DownloadTest(std::string dns);

#endif