#include <algorithm>
#include "link.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <random>
#include <list>

std::list<struct Link> links;

std::string makeurl(){
  std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
  std::random_device rd;
  std::mt19937 generator(rd());

  std::shuffle(str.begin(), str.end(), generator);
  return str.substr(0, 5);
}

std::string add_url(std::string org) {
  std::string newurl = makeurl();
  links.push_front({
    .org = org,
    .url = newurl,
  });
  return newurl;
}

std::string find_url(std::string url) {
  for(auto const& i : links) {
    if(i.url.compare(url)==0)
      return i.org;
  }
  return "";
}
