#include <iostream>

#include <pessum/pessum.hpp>

#include "committo.hpp"

int main(int argc, char const* argv[]) {
  std::string url = "https://jsonplaceholder.typicode.com/albums/1";
  std::string file = "test.txt";
  committo::InitCommitto();
  committo::SetCommitto(committo::FOLLOWLOCATION, true);
  committo::GetFile(file, url);
  std::string json_str = committo::GetString(url);
  committo::Json url_json = committo::GetJson(url);
  committo::Json json(file);
  committo::Json str_json;
  str_json.SetData(json_str);
  std::cout << url_json.String() << std::endl;
  std::cout << str_json.String() << std::endl;
  std::cout << json.String() << std::endl;
  committo::TermCommitto();
  pessum::SaveLog("out.log");
  return 0;
}
