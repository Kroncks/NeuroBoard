#pragma once

// =====================================================
// NeuroBoard Hardware Configuration
// =====================================================

// ================= NeoPixel =================
#define NEURO_RGB_PIN    38
#define NEURO_RGB_COUNT   1
#define NEURO_RGB_TYPE   (NEO_GRB + NEO_KHZ800)
#define NEURO_RGB_BRIGHTNESS 50

// ================= SD Card =================
#define NEURO_SD_CLK  40
#define NEURO_SD_CMD  39
#define NEURO_SD_DAT0 41

// ================= Camera OV3660 =================
#define NEURO_CAM_PIN_PWDN   -1
#define NEURO_CAM_PIN_RESET  -1
#define NEURO_CAM_PIN_XCLK    16
#define NEURO_CAM_PIN_SIOD    4
#define NEURO_CAM_PIN_SIOC    5
#define NEURO_CAM_PIN_D7      15
#define NEURO_CAM_PIN_D6      17
#define NEURO_CAM_PIN_D5      18
#define NEURO_CAM_PIN_D4      9
#define NEURO_CAM_PIN_D3      11
#define NEURO_CAM_PIN_D2      13
#define NEURO_CAM_PIN_D1      12
#define NEURO_CAM_PIN_D0      10
#define NEURO_CAM_PIN_VSYNC   6
#define NEURO_CAM_PIN_HREF    7
#define NEURO_CAM_PIN_PCLK    8
