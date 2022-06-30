#include <./states/config.h>
/*
    Configuration for Displayer:
        - Color of Text
        - Borders Style 
        - Outline
        - Speed
*/

LayoutType layout = LayoutType::Modern;

byte frameColor[3], stockColorGain[3], stockColorLoss[3];

LayoutType getLayout(){
    return layout;
}

void setLayout(LayoutType newLayout){
    layout = newLayout;
}