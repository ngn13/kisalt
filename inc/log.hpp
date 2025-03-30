#pragma once
#include <cstdarg>
#include <cstdio>
#include <string>

#define RED   "\x1b[31m"
#define BLUE  "\x1b[34m"
#define RESET "\x1b[0m"

void error(std::string, ...);
void info(std::string, ...);
