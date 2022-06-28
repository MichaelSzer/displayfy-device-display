#ifndef MAINH
#define MAINH

#include <Arduino.h>

enum Menu {
  GENERAL,
  STOCKS,
  CONFIG
};

// Define Macros for RGB LED Display
#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

#endif