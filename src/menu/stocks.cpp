#include <Arduino.h>
#include <main.h>
#include <states/stocks.h>
#include <RGBmatrixPanel.h>
#include <utils.h>

extern RGBmatrixPanel matrix;
unsigned long last = (unsigned long)100000000000;
std::map<String, String>::iterator it;
u_int8_t numberOfStocks = 0;

void paintFrame(u_int16_t color) {
  matrix.drawRect(0, 0, matrix.width(), 2, color);
  matrix.drawRect(0, matrix.height()-2, matrix.width(), 2, color);
  matrix.drawRect(0, 2, 2, matrix.height()-4, color);
  matrix.drawRect(matrix.width()-2, 2, 2, matrix.height()-4, color);
}

void showStock(String symbol, String price) {
  // Clean Screen First
  matrix.fillRect(2, 2, matrix.width()-4, matrix.height()-4, matrix.Color333(0,0,0));

  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.setCursor(5, 5);
  matrix.print(symbol); 
  matrix.setCursor(14,18);
  matrix.print(price);
}

void prepareDisplay(){
    paintFrame(matrix.Color333(7,7,7));
}

// wait() is a delay() without stopping the cpu
bool wait(unsigned long &last){
  if ( millis() - last < 3000 ) return false;
  last = millis();
  return true;
}

void displayStocks(){

  // Detect changes in stocks Map
  if(numberOfStocks != stocks.size()) {
    numberOfStocks = stocks.size();
    it = stocks.begin();
  }

  // If there are no stocks, don't do anything
  if(numberOfStocks == 0) return;

  if ( !wait(last) ) return;

  Serial.println("STOCKS MENU");
  showStock(it->first, it->second);

  if ( ++it == stocks.end() ) it = stocks.begin();
}