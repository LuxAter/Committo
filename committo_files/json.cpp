#include "json.hpp"
#include <vector>
#include <string>
#include <pessum.h>

void committo::Json::SetData(std::string in_data){
  std::vector<std::string> str_vec;
  std::string temp_string = "";
  for(int i =0; i < in_data.size(); i++){
    if(in_data[i] == '\n'){
      str_vec.push_back(temp_string);
      temp_string = "";
    }else{
      temp_string+=in_data[i];
    }
  }
  SetData(str_vec);
}

void committo::Json::SetData(std::vector<std::string> in_data){
  is_set = true;
  if(in_data.front() == "{"){
    in_data.erase(in_data.begin());
    in_data.erase(in_data.end());
  }
  for(int i = 0; i < in_data.size(); i++){
    while(in_data[i].front() == ' '){
      in_data[i].erase(in_data[i].begin());
    }
  }
  for(int i = 0; i < in_data.size(); i++){
    Json sub_data;
    bool set = false;
    std::vector<std::string> sub_set;
    std::string name_str = "", data_string = "";
    int j;
    int bracket_count = 0;
    for(j = 1; j < in_data[i].size() && in_data[i][j] != '\"'; j++){
      name_str += in_data[i][j];
    }
    j+=3;
    if(in_data[i][j] == '\"'){
      j++;
    }
    for(; j < in_data[i].size(); j++){
      data_string += in_data[i][j];
    }
    if(data_string.size() > 0 && data_string.back() == ','){
      data_string.pop_back();
    }
    if(data_string.size() > 0 && data_string.back() == '\"'){
      data_string.pop_back();
    }
    if(data_string == "{"){
      set = true;
      data_string += "\n";
      bracket_count++;
      i++;
      for(; i < in_data.size() && bracket_count != 0; i++){
        if(in_data[i].back() == '{'){
          bracket_count++;
        }
        if(in_data[i].front() == '}'){
          bracket_count--;
        }
        sub_set.push_back(in_data[i]);
      }
      sub_set.pop_back();
      i--;
    }
    sub_data.name = name_str;
    if(set == true){
      sub_data.SetData(sub_set);
      set = false;
    }
    else{
      sub_data.value = data_string;
      sub_data.is_set = false;
    }
    data_set.push_back(sub_data);
  }
}

std::string committo::Json::Print(int level){
  std::string str = "";
  if(is_set == true){
    for(int i = 0; i < level; i++){
      str+= ' ';
    }
    str+= name + ": {\n";
    for(int i = 0; i < data_set.size(); i++){
      str += data_set[i].Print(level + 1);
    }
    for(int i = 0; i < level; i++){
      str += ' ';
    }
    str += "}\n";
  }else{
    for(int i = 0; i < level; i++){
      str += ' ';
    }
    str+= name + ": " + value + "\n";
  }
  return(str);
}

committo::Json committo::Json::Find(std::string find_name){
  Json return_data;
  if(find_name == name){
    return(*this);
  }else{
    for(int i = 0; i < data_set.size() && return_data.name != find_name; i++){
      return_data = data_set[i].Find(find_name);
    }
  }
  return(return_data);
}
