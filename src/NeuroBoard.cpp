#include "NeuroBoard.h"
#include "config.h"

#include <Adafruit_NeoPixel.h>
#include <SD_MMC.h>


Adafruit_NeoPixel rgb(
    NEURO_RGB_COUNT,
    NEURO_RGB_PIN,
    NEURO_RGB_TYPE
);


NeuroBoardClass NeuroBoard;


bool NeuroBoardClass::begin()
{
    rgb.begin();
    rgb.setBrightness(NEURO_RGB_BRIGHTNESS);
    rgb.clear();
    rgb.show();

    return true;
}


void NeuroBoardClass::setRGB(uint8_t r, uint8_t g, uint8_t b)
{
    rgb.setPixelColor(
        0,
        rgb.Color(r,g,b)
    );

    rgb.show();
}
