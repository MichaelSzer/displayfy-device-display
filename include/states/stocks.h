#ifndef STATESSTOCKSH
#define STATESSTOCKSH

#include <Arduino.h>
#include <map>

extern std::map<String, String> stocks;

void addStock(String stock, String price);

void removeStock(String stock);

#endif