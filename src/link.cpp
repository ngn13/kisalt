#include <openssl/sha.h>
#include <json/json.h>
#include "config.hpp"
#include <algorithm>
#include <iostream>
#include "link.hpp"
#include "log.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <string>
#include <random>
#include <list>

std::list<struct Link> links;

std::string find_org(std::string org) {
  for(auto const& i : links) {
    if(i.org.compare(org)==0)
      return i.url;
  }
  return "";
}

std::string find_url(std::string url) {
  for(auto const& i : links) {
    if(i.url.compare(url)==0)
      return i.org;
  }
  return "";
}

bool load_links() {
  std::ifstream stream = std::ifstream("data/links.json");
  if(stream.fail())
    return false;

  std::string json, buf = std::string(4096, '\0');
  while (stream.read(& buf[0], 4096)) {
    json.append(buf, 0, stream.gcount());
  }
  json.append(buf, 0, stream.gcount());
  stream.close();

  Json::Value root;
  JSONCPP_STRING err;
  Json::CharReaderBuilder builder;
  
  const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
  if (!reader->parse(json.c_str(), json.c_str() + json.length(), 
        &root, &err)) {
    error("Cannot load saved links file");
    return false;
  }

  if(root["links"].empty())
    return false;
   
  for(auto const& l : root["links"]){
    links.push_front({
      .org = l["org"].asString(),
      .url = l["url"].asString(),
    });
  }

  info("Loaded total of %d saved links", root["links"].size());
  return true;
}

bool save_links() {
  if(!envsave)
    return true;

  Json::Value root, link;
  for(auto const& i : links) {
    link["url"] = i.url;
    link["org"] = i.org;
    root["links"].append(link);
  }

  Json::StreamWriterBuilder builder;
  const std::string json = Json::writeString(builder, root);
  std::ofstream jsonfile;

  jsonfile.open("data/links.json");
  if(jsonfile.fail()){
    error("Failed to open the links file");
    return false;
  }

  jsonfile << json; 
  jsonfile.close();
  return true;
}

std::string add_url(std::string org) {
  std::string found = find_org(org);
  if(!found.empty())
    return found;

  unsigned char hash[SHA_DIGEST_LENGTH];
  unsigned char orgurl[org.length()+1];
  memcpy(orgurl, org.c_str(), org.length());
  SHA1(orgurl, sizeof(orgurl)-1, hash);

  char hashhex[SHA_DIGEST_LENGTH+SHA224_DIGEST_LENGTH];
  char current[3];

  for(int i = 0; i < SHA_DIGEST_LENGTH; i++){
    sprintf(current, "%02x", hash[i]);
    strncpy(hashhex+(i*2), current, 2);
  }

  std::string hashstr(hashhex);
  std::string url = hashstr.substr(0, 5);

  links.push_front({
    .org = org,
    .url = url,
  });

  save_links();
  return url;
}
