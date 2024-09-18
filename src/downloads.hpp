#pragma once
#include <string>

struct DnsResult {
   std::string dns;
   size_t downloaded;
};

DnsResult DownloadTest(std::string dns);
