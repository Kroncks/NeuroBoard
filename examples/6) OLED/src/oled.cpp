#include <NeuroBoardS3.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 4
#define OLED_SCL 5

#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1
);

void setup()
{
    NeuroBoard.initLED();

    // LED rouge au démarrage = écran pas encore validé
    NeuroBoard.setLED(255, 0, 0);

    Wire.begin(OLED_SDA, OLED_SCL);

    // Vérification de la présence de l'écran OLED
    Wire.beginTransmission(OLED_ADDR);
    byte error = Wire.endTransmission();

    if (error != 0)
    {
        // OLED absent ou non détecté
        NeuroBoard.setLED(255, 0, 0);

        while (true)
        {
            delay(100);
        }
    }

    // Initialisation de l'écran
    if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDR
    ))
    {
        // Échec de l'initialisation
        NeuroBoard.setLED(255, 0, 0);

        while (true)
        {
            delay(100);
        }
    }

    // À partir d'ici, l'écran est bien détecté
    NeuroBoard.setLED(0, 255, 0);

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    // Police custom
    display.setFont(&FreeSans9pt7b);

    const char* title = "NeuroBoardS3";

    int16_t x1, y1;
    uint16_t w, h;

    display.getTextBounds(
        title,
        0, 0,
        &x1, &y1,
        &w, &h
    );

    display.setCursor(
        (SCREEN_WIDTH - w) / 2,
        30
    );

    display.println(title);

    // Police normale pour "by ECE"
    display.setFont(NULL);
    display.setTextSize(1);

    const char* subtitle = "by ECE";

    display.getTextBounds(
        subtitle,
        0, 0,
        &x1, &y1,
        &w, &h
    );

    display.setCursor(
        (SCREEN_WIDTH - w) / 2,
        50
    );

    display.println(subtitle);

    display.display();
}

void loop(){}