#include "downloads.hpp"

#include <curl/curl.h>

#include <string>

size_t WriteCallback(void *ptr, size_t size, size_t nmemb, void *userdata) {
  size_t totalSize{size * nmemb};
  *(size_t *)userdata += totalSize;
  return totalSize;
}

DnsResult DownloadTest(std::string dns) {
  CURLcode res{};
  size_t downloadedBytes{0};
  CURL *curl = curl_easy_init();
  std::string url{
      "https://packages.gitlab.com/gitlab/gitlab-ce/packages/el/7/"
      "gitlab-ce-16.8.0-ce.0.el7.x86_64.rpm/download.rpm"};

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, dns.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &downloadedBytes);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
  }

  return DnsResult{dns, downloadedBytes / 1024};
}