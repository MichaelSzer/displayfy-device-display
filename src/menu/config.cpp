#include <Arduino.h>
#include <main.h>

void handlerConfig(String &command, Menu &instance){
    Serial.println("CONFIG MENU");

    if ( command.equals("EXIT") )
        instance = Menu::GENERAL;

    command = "";
}