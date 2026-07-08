#include <NeuroBoard.h>


void setup()
{
  NeuroBoard.begin();
}


void loop()
{
    NeuroBoard.setRGB(255,0,0);
    delay(1000);

    NeuroBoard.setRGB(0,255,0);
    delay(1000);

    NeuroBoard.setRGB(0,0,255);
    delay(1000);
}