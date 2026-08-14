#include "NeuroBoard.h"
#include "config.h"




NeuroBoardClass::NeuroBoardClass()
:
led(
    NEURO_LED_COUNT,
    NEURO_LED_PIN,
    NEO_GRB + NEO_KHZ800
)
{
    ledOK = false;
    cameraOK = false;
    sdOK = false;
    log = true;
}

void NeuroBoardClass::neuroLog(const char *format, ...)
{
    if (!log) return;

    char buffer[256];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    Serial.println(buffer);
}

void NeuroBoardClass::setLED(uint8_t r,uint8_t g,uint8_t b)
{
    if(!ledOK) initLED();

    led.setPixelColor(
        0,
        led.Color(r,g,b)
    );

    led.show();
}


void NeuroBoardClass::setBrightnessLED(
    uint8_t brightness
)
{
    if (!ledOK) initLED();

    led.setBrightness(brightness);
}

void NeuroBoardClass::initLED()
{
    if(ledOK) return;

    led.begin();
    led.setBrightness(NEURO_LED_BRIGHTNESS);
    led.clear();
    led.show();

    ledOK = true;
}


bool NeuroBoardClass::initSD(bool formatOnFail)
{
    if (sdOK) return true;

    neuroLog("[SD] Init");

    SD_MMC.setPins(
        NEURO_SD_CLK,
        NEURO_SD_CMD,
        NEURO_SD_DAT0
    );

    if (!SD_MMC.begin("/sdcard", true, formatOnFail))
    {
        neuroLog("[SD] FAILED");

        sdOK = false;
        return false;
    }

    neuroLog("[SD] OK");

    sdOK = true;

    return true;
}

void NeuroBoardClass::deinitSD()
{
    if (!sdOK) return;

    SD_MMC.end();
    sdOK = false;

    neuroLog("[SD] Deinit");
}



bool NeuroBoardClass::initCamera()
{
    if (cameraOK) return true;

    neuroLog("[CAM] Init...");


    camera_config_t config = {};


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
        neuroLog(
            "[CAM] ERROR 0x%x",
            err
        );

        cameraOK=false;
        return false;
    }


    neuroLog("[CAM] OK");

    cameraOK=true;

    return true;
}

void NeuroBoardClass::deinitCamera()
{
    if (!cameraOK) return;

    esp_camera_deinit();
    cameraOK = false;

    neuroLog("[CAM] Deinit");
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