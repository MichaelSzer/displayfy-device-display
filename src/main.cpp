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
  setDefaultConfig();
  prepareDisplay();
}

String command;

/*
  Commands:
    - SADD|{Stock Symbol}|{Stock Price}||{Stock Price Change}||{Stock Percentage Change}': Add or update a stock to the list.
    - SDEL|{Stock Symbol}': Delete a stock from the list.
    - CONFIG|LAYOUT|{Layout Id}': Set display layout.
    - CONFIG|FRAMECOLOR|{R}|{G}|{B}': Set frame color.
    - CONFIG|BACKGROUNDCOLOR|{R}|{G}|{B}': Set background color.
    - CONFIG|STOCKCOLORLOSS|{R}|{G}|{B}': Set stock color for losses.
    - CONFIG|STOCKCOLORGAIN|{R}|{G}|{B}': Set stock color for gains.
    - CONFIG|PERIOD|{Period}': Set period of stocks display.
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
    String priceChange = params[2];
    String percentageChange = params[3];

    command = "";
    addStock(symbol, price, priceChange, percentageChange);
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
  else if(command.startsWith("CONFIG|FRAMECOLOR"))
  {
    // CONFIG FRAMECOLOR command params[0]: "FRAMECOLOR" params[1]: "{0-255}" params[2]: "{0-255}" params[3]: "{0-255}"
    std::vector<String> params = getParams(command);

    // Change Frame Color Configuration
    setFrameColor( params[1].toInt(), params[2].toInt(), params[3].toInt() );

    command = "";
  }
  else if(command.startsWith("CONFIG|BACKGROUNDCOLOR"))
  {
    // CONFIG FRAMECOLOR command params[0]: "BACKGROUNDCOLOR" params[1]: "{0-255}" params[2]: "{0-255}" params[3]: "{0-255}"
    std::vector<String> params = getParams(command);

    // Change Frame Color Configuration
    setBackgroundColor( params[1].toInt(), params[2].toInt(), params[3].toInt() );

    command = "";
  }
  else if(command.startsWith("CONFIG|STOCKCOLORLOSS"))
  {
    // CONFIG FRAMECOLOR command params[0]: "STOCKCOLORLOSS" params[1]: "{0-255}" params[2]: "{0-255}" params[3]: "{0-255}"
    std::vector<String> params = getParams(command);

    // Change Frame Color Configuration
    setStockColorLoss( params[1].toInt(), params[2].toInt(), params[3].toInt() );

    command = "";
  }
  else if(command.startsWith("CONFIG|STOCKCOLORGAIN"))
  {
    // CONFIG FRAMECOLOR command params[0]: "FRAMECOLOR" params[1]: "{0-255}" params[2]: "{0-255}" params[3]: "{0-255}"
    std::vector<String> params = getParams(command);

    // Change Frame Color Configuration
    setStockColorGain( params[1].toInt(), params[2].toInt(), params[3].toInt() );

    command = "";
  }else if(command.startsWith("CONFIG|PERIOD"))
  {
    // CONFIG FRAMECOLOR command params[0]: "FRAMECOLOR" params[1]: "{0-255}" params[2]: "{0-255}" params[3]: "{0-255}"
    std::vector<String> params = getParams(command);

    // Change Frame Color Configuration
    setPeriod( params[0].toInt() );

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