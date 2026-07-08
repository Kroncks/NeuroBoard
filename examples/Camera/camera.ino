#include <NeuroBoard.h>


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
    NeuroBoard.begin();

    if(!NeuroBoard.initCamera())
    {
        NeuroBoard.setRGB(255, 0, 0);
        return;
    }

    if(!NeuroBoard.initSD())
    {
        NeuroBoard.setRGB(255, 0, 0);
        return;
    }

    if(capturePhotoToSD())
    {
        NeuroBoard.setRGB(0, 255, 0);
    }
    else
    {
        NeuroBoard.setRGB(255, 0, 0);
    }
}


void loop(){}