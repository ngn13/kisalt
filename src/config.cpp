#include "config.hpp"

std::string envurl = nullptr==getenv("URL") ? "http://127.0.0.1:8080/" : getenv("URL");
bool envsave = nullptr==getenv("NOSAVE");
