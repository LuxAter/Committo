#include "get.hpp"
#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <pessum/pessum.hpp>
#include "committo_core.hpp"
#include "json.hpp"

static size_t committo::WriteCallback(void* contents, size_t size, size_t nmemb,
                                      void* userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return (size * nmemb);
}

committo::Json committo::GetJson(std::string url, ...) {
  std::string return_string = GetString(url);
  Json return_json;
  return_json.SetData(return_string);
  return (return_json);
}

std::string committo::GetString(std::string url, ...) {
  std::string return_string;
  va_list args, buff_args;
  va_start(args, url);
  va_start(buff_args, url);
  ssize_t buffer_size = vsnprintf(NULL, 0, url.c_str(), buff_args);
  char* formated_url = new char[buffer_size + 1];
  formated_url[buffer_size] = '\0';
  vsprintf(formated_url, url.c_str(), args);
  va_end(args);
  va_end(buff_args);
  url = std::string(formated_url);
  if (curl_handle != NULL) {
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION,
                     committo::WriteCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &return_string);
    curl_output = curl_easy_perform(curl_handle);
    if (curl_output != CURLE_OK) {
      pessum::Log(pessum::WARNING, "Failed to get from: \"%s\"",
                  "committo::GetString", url.c_str());
      pessum::Log(pessum::ERROR, "Curl error: %s", "curl",
                  curl_easy_strerror(curl_output));
    } else {
      pessum::Log(pessum::SUCCESS, "Retreaved from: \"%s\"",
                  "committo::GetString", url.c_str());
    }
  }
  return (return_string);
}

void committo::GetFile(std::string file, std::string url, ...) {
  std::string return_string = GetString(url);
  std::ofstream save(file.c_str());
  if (save.is_open()) {
    save << return_string;
    save.close();
  }
}
