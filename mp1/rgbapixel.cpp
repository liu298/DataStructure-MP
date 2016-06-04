#include "rgbapixel.h"

RGBAPixel::RGBAPixel(){
    alpha = 255;
    red = 255;
    green = 255;
    blue = 255;
}

RGBAPixel::RGBAPixel(uint8_t r, uint8_t g, uint8_t b){
    alpha = 255;
    
    red = r;
    green = g;
    blue = b;
}
