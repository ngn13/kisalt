#include "log.hpp"

#include <cstdarg>
#include <cstdio>
#include <string>

void error(std::string msg, ...) {
  va_list args;
  va_start(args, msg);

  printf(RED "[fail] " RESET);
  vprintf(msg.c_str(), args);
  printf(RESET "\n");

  va_end(args);
}

void info(std::string msg, ...) {
  va_list args;
  va_start(args, msg);

  printf(BLUE "[info] " RESET);
  vprintf(msg.c_str(), args);
  printf(RESET "\n");

  va_end(args);
}
