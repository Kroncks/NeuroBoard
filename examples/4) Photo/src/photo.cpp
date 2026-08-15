#include <NeuroBoardS3.h>


static bool capturePhotoToSD()
{
    char photoPath[32];
    snprintf(photoPath, sizeof(photoPath), "/photo_%lu.jpg", (unsigned long)millis());

    camera_fb_t* fb = esp_camera_fb_get();
    if(!fb)
    {
        return false;
    }

    File file = SD_MMC.open(photoPath, FILE_WRITE);
    if(!file)
    {
        esp_camera_fb_return(fb);
        return false;
    }

    bool ok = file.write(fb->buf, fb->len) == fb->len;
    file.close();
    esp_camera_fb_return(fb);

    return ok;
}


void setup()
{
    Serial.begin(9600);
    NeuroBoard.initLED();

    NeuroBoard.initCamera();
    NeuroBoard.initSD();

    if(!NeuroBoard.hasCamera() && !NeuroBoard.hasSD())
    {
        NeuroBoard.setLED(255, 0, 0); // rouge
        return;
    } else if (!NeuroBoard.hasCamera())
    {
        NeuroBoard.setLED(148, 0, 211); // violet
        return;
    } else if (!NeuroBoard.hasSD())
    {
        NeuroBoard.setLED(255, 165, 0); // orange
        return;
    }

    if(capturePhotoToSD())
    {
        NeuroBoard.setLED(0, 255, 0); // vert
    }
    else
    {
        NeuroBoard.setLED(255, 0, 0); // rouge
    }
}


void loop(){}
