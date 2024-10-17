#ifndef BEST403UNLOCKER_SRC_DOWNLOADS_HPP
#define BEST403UNLOCKER_SRC_DOWNLOADS_HPP

#include <string>

struct DnsResult {
  std::string dns;
  size_t downloaded;
};

DnsResult DownloadTest(std::string dns);

#endif