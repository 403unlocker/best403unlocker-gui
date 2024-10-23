#include "config.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <toml++/toml.hpp>

const static std::string DEFAULT_DNS_LIST[] = {
    "178.22.122.100", "185.51.200.2",  "78.157.42.100", "78.157.42.101",
    "10.202.10.202",  "10.202.10.102", "185.55.226.26", "185.55.225.25",
    "10.202.10.10",   "10.202.10.11"};

const static std::string DEFAULT_DOWNLOAD_URL =
    "https://packages.gitlab.com/gitlab/gitlab-ce/packages/el/7/"
    "gitlab-ce-16.8.0-ce.0.el7.x86_64.rpm/download.rpm";

static std::string GetConfigFilePath() {
  std::string username = GetUsername();
  std::filesystem::path folderPath{};
  const std::filesystem::path configFileName = "config.toml";

#ifdef _WIN32
  folderPath = "C:\\Users\\" + username + "\\.best403unlocker-gui";
#elif __linux__
  folderPath = "/home/" + username + "/.config/best403unlocker-gui";
#endif

  if (!std::filesystem::exists(folderPath))
    std::filesystem::create_directory(folderPath);

  const std::filesystem::path configFilePath = folderPath / configFileName;

  if (!std::filesystem::exists(configFilePath)) {
    std::ofstream output = std::ofstream{configFilePath, std::ios_base::binary};
    if (output.is_open()) {
      output << "[settings]\n";
      output << "dns = [";
      int dnsListSize = sizeof(DEFAULT_DNS_LIST) / sizeof(DEFAULT_DNS_LIST[0]);

      for (int i = 0; i < dnsListSize; i++)
        output << '"' << DEFAULT_DNS_LIST[i] << '"'
               << (i == dnsListSize - 1 ? "" : ", ");

      output << "]\n";
      output << "url = " << '"' << DEFAULT_DOWNLOAD_URL << '"';
    }
    output.close();
  }

  return (folderPath / configFileName).string();
}

std::string GetUsername() {
#ifdef _WIN32
  char *user = std::getenv("USERNAME");
#elif __linux__
  char *user = std::getenv("USER");
#endif

  return std::string{user == nullptr ? "" : user};
}

std::vector<std::string> GetDNSConfig() {
  std::vector<std::string> result{};
  toml::table configTable = toml::parse_file(GetConfigFilePath());
  toml::array &tomlDnsList = *configTable["settings"]["dns"].as_array();

  for (auto &&data : tomlDnsList) {
    result.push_back(data.value_or<std::string>(""));
  }

  return result;
}

std::string GetTestingURL() {
  std::string configPath = GetConfigFilePath();
  toml::table configTable = toml::parse_file(configPath);

  return configTable["settings"]["url"].value_or(DEFAULT_DOWNLOAD_URL);
}
