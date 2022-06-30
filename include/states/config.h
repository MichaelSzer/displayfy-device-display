#ifndef STATESCONFIGH
#define STATESCONFIGH

#include <Arduino.h>

enum LayoutType {
    Simple, // Layout Id 0
    Three, // Layout Id 1
    Modern // Layout Id 2
};

void setLayout(LayoutType);
LayoutType getLayout();

void setFrameColor(byte r, byte g, byte b);
byte* getFrameColor();

void setColorGain(byte r, byte g, byte b);
byte* getColorGain();

void setColorLoss(byte r, byte g, byte b);
byte* getColorLoss();

#endif