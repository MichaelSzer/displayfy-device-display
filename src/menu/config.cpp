#include <Arduino.h>
#include <main.h>
#include <RGBmatrixPanel.h>

extern RGBmatrixPanel matrix;

void handlerConfig(String &command, Menu &instance){
    Serial.println("CONFIG MENU");

    if ( command.equals("EXIT") )
        instance = Menu::GENERAL;

    command = "";
}