#ifndef STATESSTOCKSH
#define STATESSTOCKSH

#include <Arduino.h>
#include <map>

struct Stock
{
    String price;
    String priceChange;
    String percentageChange;
};

extern std::map<String, Stock> stocks;

void addStock(String stock, String price, String priceChange, String percentageChange);

void removeStock(String stock);

#endif