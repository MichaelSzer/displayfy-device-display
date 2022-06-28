#ifndef UTILSH
#define UTILSH

#include <vector>
#include <Arduino.h>

std::vector<String> getParams(String command);

bool wait(unsigned long &last);

#endif