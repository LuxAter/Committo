#ifndef COMMITTO_GET_HPP
#define COMMITTO_GET_HPP
#include <string>
#include "json.hpp"
namespace committo {
  static size_t WriteCallback(void* contents, size_t size, size_t nmemb,
                              void* userp);
  Json GetJson(std::string url, ...);
  std::string GetString(std::string url, ...);
  void GetFile(std::string file_path, std::string url, ...);
}
#endif
