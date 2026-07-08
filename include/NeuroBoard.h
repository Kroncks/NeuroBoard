#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


class NeuroBoardClass {

private:

    Adafruit_NeoPixel rgb;

    bool cameraOK;
    bool sdOK;


public:

    NeuroBoardClass();


    void begin();


    void setRGB(
        uint8_t r,
        uint8_t g,
        uint8_t b
    );


    bool initCamera();


    bool initSD();


    bool hasCamera();


    bool hasSD();

};


extern NeuroBoardClass NeuroBoard;