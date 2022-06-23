#include <Arduino.h>
#include <main.h>

void handlerGeneral(String &command, Menu &instance){
    Serial.println("GENERAL MENU");

    if ( command.equals("STOCKS") ){
        Serial.println(" -- STOCKS ");
        instance = Menu::STOCKS;
    }else if ( command.equals("CONFIG") )
        instance = Menu::CONFIG;

    command = "";
}