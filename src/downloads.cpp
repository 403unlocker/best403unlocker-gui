#include "downloads.h"

#include <curl/curl.h>

#include <string>

#include "config.h"

inline static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, void *userdata) {
  size_t totalSize{size * nmemb};
  *(size_t *)userdata += totalSize;
  return totalSize;
}

DnsResult DownloadTest(std::string dns) {
  CURLcode res{};
  size_t downloadedBytes{0};
  CURL *curl = curl_easy_init();
  std::string url = GetTestingURL();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, dns.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &downloadedBytes);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
  }

  return DnsResult{dns, downloadedBytes / 1024};
}