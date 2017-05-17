#include <pessum.h>
#include <fstream>
#include <iostream>
#include "committo.h"

int main(int argc, char const* argv[]) {
  // std::string url = "http://als.lbl.gov/beam-status/";
  std::string url = "https://jsonplaceholder.typicode.com/albums/1";
  std::string file = "test.txt";
  committo::InitCommitto();
  committo::SetCommitto(committo::FOLLOWLOCATION, true);
  committo::GetFile(file, url);
  committo::TermCommitto();
  pessum::SaveLog("out.log");
  return 0;
}
