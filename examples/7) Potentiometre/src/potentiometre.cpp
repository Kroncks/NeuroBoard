#include <NeuroBoardS3.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PIN_POT 1

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

float valuePot = 0.0;

void setup()
{
    pinMode(PIN_POT, INPUT);
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
    }

    // Initialisation de l'écran
    if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDR
    ))
    {
        // Échec de l'initialisation
        NeuroBoard.setLED(255, 0, 0);
    }
    
    display.clearDisplay();
    display.display();

    NeuroBoard.setLED(0, 255, 0);

    delay(1000);

    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
}

void loop()
{
    valuePot = analogRead(PIN_POT) * 100.0 / 4095.0;

    display.clearDisplay();

    // Convertit la valeur en texte
    char text[10];
    sprintf(text, "%.1f%%", valuePot);

    // Calcule la taille du texte
    int16_t x1, y1;
    uint16_t w, h;

    display.getTextBounds(
        text,
        0, 0,
        &x1, &y1,
        &w, &h
    );

    // Centre horizontalement
    int x = (SCREEN_WIDTH - w) / 2;

    // Centre verticalement
    int y = (SCREEN_HEIGHT - h) / 2 - y1;

    display.setCursor(x, y);
    display.print(text);

    display.display();

    
    NeuroBoard.setBrightnessLED(valuePot * 255.0 / 100.0);
    NeuroBoard.setLED(20, 140, 50);
    delay(20);
}