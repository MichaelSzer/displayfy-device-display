#ifndef STATESCONFIGH
#define STATESCONFIGH

#include <Arduino.h>

enum LayoutType {
    Simple, // Layout Id 0
    Three, // Layout Id 1
    Modern // Layout Id 2
};

void setDefaultConfig();

void setLayout(LayoutType);
LayoutType getLayout();

void setFrameColor(byte r, byte g, byte b);
u_int16_t getFrameColor();

void setBackgroundColor(byte r, byte g, byte b);
u_int16_t getBackgroundColor();

void setStockColorGain(byte r, byte g, byte b);
u_int16_t getStockColorGain();

void setStockColorLoss(byte r, byte g, byte b);
u_int16_t getStockColorLoss();

void setPeriod(u_int32_t period);
u_int32_t getPeriod();

#endif