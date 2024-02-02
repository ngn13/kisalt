#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>

extern std::list<struct Link> links;
struct Link {
  std::string org;
  std::string url;
};

std::string add_url(std::string);
std::string find_url(std::string);
