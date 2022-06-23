#include <main.h>
#include <Arduino.h>
#include <menu/general.h>
#include <menu/stocks.h>
#include <menu/config.h>
#include <states/stocks.h>
#include <utils.h>

Menu instance = Menu::GENERAL;

void setup() {
  Serial.begin(9600, SERIAL_8N1);
  Serial1.begin(9600, SERIAL_8N1);
  while(!Serial && !Serial1);

  Serial.setTimeout(1000);
  pinMode(LED_BUILTIN, OUTPUT);
}

String command;

/*
  Commands:
    - SADD|{Stock Symbol}|{Stock Price}': Add or update a stock to the list.
    - SDEL|{Stock Symbol}': Delete a stock from the list.
    - GENERAL': Go to main menu.
    - CONFIG': Go to the configuration menu.
    - STOCKS': Go to the stocks menu
*/
void loop() {

  // Read next Command
  if(Serial.available()){
    command = Serial.readStringUntil('\'');
    Serial.println(command);
  }

  if(command.startsWith("SADD"))
  {

    // SADD command
    std::vector<String> params = getParams(command);
    String symbol = params[0];
    String price = params[1];

    command = "";
    addStock(symbol, price);
  }
  else if(command.startsWith("SDEL"))
  {
    // SDEL command
    std::vector<String> params = getParams(command);
    String symbol = params[0];
    
    command = "";
    removeStock(symbol);
  }

  switch(instance){
    case Menu::GENERAL:
      handlerGeneral(command, instance);
      break;
    case Menu::CONFIG:
      handlerConfig(command, instance);
      break;
    case Menu::STOCKS:
      handlerStocks(command, instance);
      break;
    default:
      break;
  }
  delay(1000);
}