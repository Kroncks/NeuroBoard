#include <Arduino.h>

#define LED_PIN 0

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    delay(2000);
}

void loop()
{
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
}
