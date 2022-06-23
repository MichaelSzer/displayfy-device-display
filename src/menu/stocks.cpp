#include <Arduino.h>
#include <main.h>
#include <states/stocks.h>

void handlerStocks(String &command, Menu &instance){
    Serial.println("STOCKS MENU");

    if(stocks.empty()){
        addStock("TSLA", "1852.20");
        addStock("MSFT", "521.80");
    }

    // Iterate through map -- Show Stocks in Displayer
    auto iter = stocks.begin();
    while(iter != stocks.end()){
        Serial.println(" -- " + iter->first + " " + iter->second);
        iter++;
    }

    if ( command.equals("EXIT") )
        instance = Menu::GENERAL;

    command = "";
}