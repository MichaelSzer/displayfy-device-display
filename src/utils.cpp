#include <utils.h>

std::vector<String> getParams(String command){
  std::vector<String> params = {};

  int i = 0;
  while(command[i++] != '|');
  
  while(u_int16_t(i) < command.length()){
    String param;

    while(command[i] != '|' && u_int16_t(i) < command.length()){ 
      param += command[i];
      i++;
    }

    i++;
    params.push_back(param);
  }

  return params;
}