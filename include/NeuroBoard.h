#pragma once

#include <Arduino.h>

class NeuroBoardClass {

public:

    void begin();


    void setRGB(
        uint8_t r,
        uint8_t g,
        uint8_t b
    );


    bool cameraInit();


    bool sdInit();


    bool psramTest();

};


extern NeuroBoardClass NeuroBoard;