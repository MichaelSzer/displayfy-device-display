#include <main.h>
#include <Arduino.h>
#include <menu/general.h>
#include <menu/stocks.h>
#include <menu/config.h>
#include <states/config.h>
#include <states/stocks.h>
#include <utils.h>
#include <RGBmatrixPanel.h>

Menu instance = Menu::STOCKS;
extern RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

void setup() {
  Serial.begin(9600, SERIAL_8N1);
  Serial1.begin(9600, SERIAL_8N1);
  while(!Serial1);
  pinMode(LED_BUILTIN, OUTPUT);

  // RGB Matrix Begin
  matrix.begin();
  prepareDisplay();
}

String command;

/*
  Commands:
    - SADD|{Stock Symbol}|{Stock Price}': Add or update a stock to the list.
    - SDEL|{Stock Symbol}': Delete a stock from the list.
    - CONFIG|LAYOUT|{Layout Id}': Set display layout.
    - GENERAL': Go to main menu.
    - CONFIG': Go to the configuration menu.
    - STOCKS': Go to the stocks menu
*/
void loop() {

  // Read next Command
  if(Serial1.available()){
    command = Serial1.readStringUntil('\'');
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
  else if(command.startsWith("CONFIG|LAYOUT"))
  {
    // CONFIG LAYOUT command params[0]: "LAYOUT" params[1]: "{0,1,2}"
    std::vector<String> params = getParams(command);

    // Change Layout Configuration
    switch(params[1].toInt()){
      case 0:
        setLayout(LayoutType::Simple);
        break;
      case 1:
        setLayout(LayoutType::Three);
        break;
      case 2:
        setLayout(LayoutType::Modern);
        break;
    }

    // Refresh Display Layout
    if(instance == Menu::STOCKS)
      prepareDisplay();

    command = "";
  }

  switch(instance){
    case Menu::GENERAL:
      handlerGeneral(command, instance);
      break;
    case Menu::CONFIG:
      handlerConfig(command, instance);
      break;
    case Menu::STOCKS:
      displayStocks();
      break;
    default:
      break;
  }
  delay(250);
}