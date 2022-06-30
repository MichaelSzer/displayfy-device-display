#include <menu/stocks.h>
#include <Arduino.h>
#include <main.h>
#include <states/stocks.h>
#include <RGBmatrixPanel.h>
#include <utils.h>
#include <states/config.h>

extern RGBmatrixPanel matrix;
unsigned long last = (unsigned long)100000000000;
std::map<String, String>::iterator it;
u_int8_t numberOfStocks = 0;

/*
    Work Pending
        - Three Layout
        - Modern Layout
        - Get Colors from Configuration 
*/

/*
  Classic Layout
*/
void paintFrameSimple() {
    // Clean Screen First
    matrix.fillRect(0, 0, matrix.width(), matrix.height(), getBackgroundColor());

    matrix.drawRect(0, 0, matrix.width(), 2, getFrameColor());
    matrix.drawRect(0, matrix.height()-2, matrix.width(), 2, getFrameColor());
    matrix.drawRect(0, 2, 2, matrix.height()-4, getFrameColor());
    matrix.drawRect(matrix.width()-2, 2, 2, matrix.height()-4, getFrameColor());
}

void showStocksSimple(String symbol, String price) {
  // Clean Screen First
  matrix.fillRect(2, 2, matrix.width()-4, matrix.height()-4, matrix.Color333(0,0,0));

  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.setCursor(5, 5);
  matrix.print(symbol); 
  matrix.setCursor(14,18);
  matrix.print(price);
}

/*
  Three Layout
*/
u_int8_t place = 0;

void paintFrameThree() {
    // Clean Screen First
    matrix.fillRect(0, 0, matrix.width(), matrix.height(), getBackgroundColor());
    
    matrix.drawRect(0, 10, matrix.width(), 1, getFrameColor());
    matrix.drawRect(0, 21, matrix.width(), 1, getFrameColor());

    // Reset
    place = 0;
}

void showStocksThree(String symbol, String price) {

    // Clean Screen Text Place
    matrix.fillRect(0, (place * 11), matrix.width(), 10, getBackgroundColor());

    if(price == "") return;

    // Limit price to 5 digits
    price = price.indexOf('.') < 0? price.substring(0, 5) : price.substring(0, 6); 

    matrix.setTextSize(1);
    matrix.setTextColor(getStockColorLoss());
    matrix.setCursor(1, 1 + (place * 11));
    matrix.print(symbol);
    matrix.setCursor(matrix.getCursorX()+5, matrix.getCursorY());
    for(char c : price){
        if(c == '.'){
            matrix.drawRect((int)matrix.getCursorX(), matrix.getCursorY()+5, 2, 2, getStockColorLoss());
            matrix.setCursor(matrix.getCursorX()+4, matrix.getCursorY());
        }else
            matrix.print(c);
    }
    //matrix.printf("%s $%s", symbol, price);

    
    if((numberOfStocks >= 3 && ++place > 2)
        || (numberOfStocks == 2 && ++place > 1)
            || (numberOfStocks == 1)
                || (numberOfStocks == 0)) place = 0;
}

/*
  Modern Layout
*/

// To-Do

/*
  Image Background Layout
*/

// To-Do

void prepareDisplay(){
    switch(getLayout()){
        case LayoutType::Simple:
            paintFrameSimple();
            break;
        case LayoutType::Three:
            paintFrameThree();
            break;
        case LayoutType::Modern:
            break;
    }
}

// wait() is a delay() without stopping the cpu
bool wait(unsigned long &last){
  if ( millis() - last < 3000 ) return false;
  last = millis();
  return true;
}

void displayStocks(){

    // Detect changes in stocks Map
    if(numberOfStocks != stocks.size()) prepareDisplay(), numberOfStocks = stocks.size();
    
    if(numberOfStocks == 0 || it == stocks.end()) {
        it = stocks.begin();
    }

    String price, symbol;

    // If there are no stocks, show empty screen
    if(numberOfStocks != 0) 
        price = it->second, symbol = it->first;
    else
        price = "", symbol = "";

    if ( !wait(last) ) return;

    switch(getLayout()){
        case LayoutType::Simple:
            showStocksSimple(symbol, price);
            break;
        case LayoutType::Three:
            showStocksThree(symbol, price);
            break;
        case LayoutType::Modern:
            break;
    }

    if ( numberOfStocks != 0 ) it++;
}