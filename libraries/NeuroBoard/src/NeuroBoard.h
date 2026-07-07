#pragma once

#include <Arduino.h>
#include "esp_camera.h"

class NeuroBoardClass
{
public:

    // Initialise la carte
    bool begin();

    // RGB LED
    void setRGB(uint8_t r, uint8_t g, uint8_t b);
    void clearRGB();

    // Camera
    bool beginCamera();
    camera_fb_t* capture();
    void release(camera_fb_t* frame);

    // SD
    bool beginSD();
    bool saveImage(const char* filename, camera_fb_t* frame);

};

extern NeuroBoardClass NeuroBoard;
