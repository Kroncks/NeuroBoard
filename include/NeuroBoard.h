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
    bool rgbOK;

    void logMessagef(
        const char* format,
        ...
    );

public:

    NeuroBoardClass();

    bool initRGB();
    bool initCamera();
    bool initSD();

    bool log;

    void setRGB(
        uint8_t r,
        uint8_t g,
        uint8_t b
    );

    void setBrightnessRGB(uint8_t brightness);

    bool hasCamera();
    bool hasSD();
};


extern NeuroBoardClass NeuroBoard;