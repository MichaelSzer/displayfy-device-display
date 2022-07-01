#include <./states/config.h>
#include <RGBmatrixPanel.h>
/*
    Configuration for Displayer:
        - Color of Text
        - Borders Style 
        - Outline
        - Speed
*/

LayoutType layout = LayoutType::Modern;
extern RGBmatrixPanel matrix;

u_int16_t frameColor, backgroundColor, stockColorGain, stockColorLoss;
u_int32_t period;

void setDefaultConfig(){
    frameColor = matrix.Color333(7,7,7);
    backgroundColor = matrix.Color333(0,0,0);
    stockColorGain = matrix.Color333(0,7,0);
    stockColorLoss = matrix.Color333(7,0,0);
    period = 3000;
}

LayoutType getLayout(){
    return layout;
}

void setLayout(LayoutType newLayout){
    layout = newLayout;
}

void setFrameColor(u_int8_t r, u_int8_t g, u_int8_t b){
    frameColor = matrix.Color888(r,g,b);
}

u_int16_t getFrameColor(){
    return frameColor;
}

void setBackgroundColor(u_int8_t r, u_int8_t g, u_int8_t b){
    backgroundColor = matrix.Color888(r,g,b);
}

u_int16_t getBackgroundColor(){
    return backgroundColor;
}

void setStockColorGain(u_int8_t r, u_int8_t g, u_int8_t b){
    stockColorGain = matrix.Color888(r,g,b);
}

u_int16_t getStockColorGain(){
    return stockColorLoss;
}

void setStockColorLoss(u_int8_t r, u_int8_t g, u_int8_t b){
    stockColorLoss = matrix.Color888(r,g,b);
}

u_int16_t getStockColorLoss(){
    return stockColorLoss;
}

void setPeriod(u_int32_t newPeriod){
    period = newPeriod;
}

u_int32_t getPeriod(){
    return period;
}