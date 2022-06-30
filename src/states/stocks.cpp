/*
    Stocks to show:
        - Stock
            - Symbol
            - Price
*/
#include <states/stocks.h>

/*
    Work Pending
        - Create Stock structure with price & daily change
*/

std::map<String, String> stocks = {};

void addStock(String stock, String price){
    stocks[stock] = price;
}

void removeStock(String stock){
    stocks.erase(stock);
}