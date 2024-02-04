#pragma once
#include <openssl/sha.h>
#include <json/json.h>
#include "config.hpp"
#include <algorithm>
#include <iostream>
#include "link.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <string>
#include <random>
#include <list>

extern std::list<struct Link> links;
struct Link {
  std::string org;
  std::string url;
};

std::string add_url(std::string);
std::string find_url(std::string);
bool load_links();
