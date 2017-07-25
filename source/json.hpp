#ifndef COMMITTO_JSON_HPP
#define COMMITTO_JSON_HPP
#include <string>
#include <vector>
namespace committo {
  class Json {
   public:
    Json();
    Json(std::string file);
    ~Json();
    void SetData(std::string in_data);
    void SetData(std::vector<std::string> in_data);
    std::string String(int level = 0);
    std::string name, value;
    bool is_set;
    Json Find(std::string find_name);
    std::vector<Json> data_set;

   private:
  };
};
#endif
