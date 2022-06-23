/*
    Stocks to show:
        - Stock
            - Symbol
            - Price
*/
#include <states/stocks.h>

std::map<String, String> stocks = {};

void addStock(String stock, String price){
    stocks[stock] = price;
}

void removeStock(String stock){
    stocks.erase(stock);
}