#include <cstdarg>
#include "log.hpp"
#include <cstdio>
#include <string>

void error(std::string msg, ...){
  va_list args;
  va_start(args, msg);

  printf(BOLD RED "ERROR: " RESET);
  vprintf(msg.c_str(), args);
  printf(RESET"\n");
  
  va_end(args);
}

void info(std::string msg, ...){
  va_list args;
  va_start(args, msg);

  printf(BOLD BLUE "INFO : " RESET);
  vprintf(msg.c_str(), args);
  printf(RESET"\n");
  
  va_end(args);
}
