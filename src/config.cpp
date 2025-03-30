#include "config.hpp"

std::string config_url  = nullptr == getenv("URL") ? "http://127.0.0.1:8080/" : getenv("URL");
bool        config_save = nullptr == getenv("NOSAVE");
