#include <curl/curl.h>
#include <pessum/pessum.hpp>
#include "committo_core.hpp"

namespace committo {
  CURL* curl_handle = NULL;
  CURLcode curl_output;
}

void committo::InitCommitto() {
  curl_handle = curl_easy_init();
  if (!curl_handle) {
    pessum::Log(pessum::ERROR, "Curl failed to initialize",
                "committo::InitCommitto()");
    curl_handle = NULL;
  }
}

void committo::TermCommitto() {
  if (curl_handle != NULL) {
    curl_easy_cleanup(curl_handle);
  }
}

void committo::SetCommitto(int setting, int value) {
  if (setting == FOLLOWLOCATION) {
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, (long)value);
  }
}
