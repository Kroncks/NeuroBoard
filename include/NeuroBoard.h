#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <stdarg.h>
#include <stdio.h>
#include "esp_camera.h"
#include <SD_MMC.h>


class NeuroBoardClass {

private:

    Adafruit_NeoPixel rgb;

    bool cameraOK;
    bool sdOK;


public:

    NeuroBoardClass();


    bool log;


    void begin();


    void setRGB(
        uint8_t r,
        uint8_t g,
        uint8_t b
    );


    bool initCamera();


    bool initSD();


    void logMessagef(
        const char* format,
        ...
    );


    bool hasCamera();


    bool hasSD();

};


extern NeuroBoardClass NeuroBoard;