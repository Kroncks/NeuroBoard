#include "NeuroBoard.h"
#include "config.h"




NeuroBoardClass::NeuroBoardClass()
:
rgb(
    NEURO_RGB_COUNT,
    NEURO_RGB_PIN,
    NEO_GRB + NEO_KHZ800
)
{
    cameraOK = false;
    sdOK = false;
    log = true;
}



void NeuroBoardClass::begin()
{
    Serial.begin(NEURO_BAUD_RATE);

    rgb.begin();
    rgb.setBrightness(NEURO_RGB_BRIGHTNESS);

    setRGB(0,61,62); // demi boot ece

    unsigned long start = millis();
    while (!Serial && (millis() - start < 3000)) {
        ; // attend max 3 secondes
    }

    delay(100);

    setRGB(0,122,123); // boot ece

    logMessagef("[NeuroBoard] Init OK");
}



void NeuroBoardClass::logMessagef(
    const char* format,
    ...
)
{
    if(!log)
    {
        return;
    }

    va_list args;
    va_start(args, format);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    Serial.println(buffer);
    va_end(args);
}




void NeuroBoardClass::setRGB(
    uint8_t r,
    uint8_t g,
    uint8_t b
)
{
    rgb.setPixelColor(
        0,
        rgb.Color(r,g,b)
    );

    rgb.show();
}


void NeuroBoardClass::setBrightnessRGB(
    uint8_t brightness
)
{
    rgb.setBrightness(
        brightness
    );
}




bool NeuroBoardClass::initSD()
{

    logMessagef("[SD] Init");


    SD_MMC.setPins(
        NEURO_SD_CLK,
        NEURO_SD_CMD,
        NEURO_SD_DAT0
    );


    if(!SD_MMC.begin("/sdcard",true,true))
    {
        logMessagef("[SD] FAILED");

        sdOK=false;
        return false;
    }


    logMessagef("[SD] OK");

    sdOK=true;

    return true;
}





bool NeuroBoardClass::initCamera()
{

    logMessagef("[CAM] Init...");


    camera_config_t config;


    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer   = LEDC_TIMER_0;


    config.pin_d0 = NEURO_CAM_D0;
    config.pin_d1 = NEURO_CAM_D1;
    config.pin_d2 = NEURO_CAM_D2;
    config.pin_d3 = NEURO_CAM_D3;

    config.pin_d4 = NEURO_CAM_D4;
    config.pin_d5 = NEURO_CAM_D5;
    config.pin_d6 = NEURO_CAM_D6;
    config.pin_d7 = NEURO_CAM_D7;


    config.pin_xclk = NEURO_CAM_XCLK;

    config.pin_pclk  = NEURO_CAM_PCLK;
    config.pin_vsync = NEURO_CAM_VSYNC;
    config.pin_href  = NEURO_CAM_HREF;


    config.pin_sccb_sda = NEURO_CAM_SIOD;
    config.pin_sccb_scl = NEURO_CAM_SIOC;


    config.pin_pwdn  = NEURO_CAM_PWDN;
    config.pin_reset = NEURO_CAM_RESET;


    config.xclk_freq_hz = 20000000;


    config.pixel_format = PIXFORMAT_JPEG;


    if(psramFound())
    {
        config.frame_size = FRAMESIZE_QXGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
        config.fb_location = CAMERA_FB_IN_PSRAM;
    }
    else
    {
        config.frame_size = FRAMESIZE_VGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }


    esp_err_t err = esp_camera_init(&config);


    if(err != ESP_OK)
    {
        logMessagef(
            "[CAM] ERROR 0x%x",
            err
        );

        cameraOK=false;
        return false;
    }


    logMessagef("[CAM] OK");

    cameraOK=true;

    return true;
}




bool NeuroBoardClass::hasCamera()
{
    return cameraOK;
}



bool NeuroBoardClass::hasSD()
{
    return sdOK;
}




NeuroBoardClass NeuroBoard;