/*
    Stocks to show:
        - Stock
            - Symbol
            - Price
*/
#include <states/stocks.h>

std::map<String, Stock> stocks = {};

void addStock(String stock, String price, String priceChange, String percentageChange){
    stocks[stock] = {};
    stocks[stock].price = price;
    stocks[stock].priceChange = priceChange;
    stocks[stock].percentageChange = percentageChange;
}

void removeStock(String stock){
    stocks.erase(stock);
}