#include <openssl/sha.h>
#include <algorithm>
#include <iostream>
#include "link.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <random>
#include <list>

std::list<struct Link> links;

std::string add_url(std::string org) {
  std::string found = find_url(org);
  if(!found.empty())
    return found;

  unsigned char hash[SHA_DIGEST_LENGTH];
  unsigned char orgurl[org.length()+1];
  memcpy(orgurl, org.c_str(), org.length());
  SHA1(orgurl, sizeof(orgurl)-1, hash);

  char hashhex[SHA_DIGEST_LENGTH+SHA224_DIGEST_LENGTH];
  for(int i = 0; i < SHA_DIGEST_LENGTH; i++){
    if(i == 0){
      sprintf(hashhex, "%02x", hash[i]);
      continue;
    }
    sprintf(hashhex, "%s%02x", hashhex, hash[i]);
  }

  std::string hashstr(hashhex);
  std::string url = hashstr.substr(0, 5);

  links.push_front({
    .org = org,
    .url = url,
  });

  return url;
}

std::string find_url(std::string url) {
  for(auto const& i : links) {
    if(i.url.compare(url)==0)
      return i.org;
  }
  return "";
}
