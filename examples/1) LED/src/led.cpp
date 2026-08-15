#include <NeuroBoardS3.h>


void setup()
{
  NeuroBoard.initLED();
}


void loop()
{
    NeuroBoard.setLED(255,0,0);
    delay(1000);

    NeuroBoard.setLED(0,255,0);
    delay(1000);

    NeuroBoard.setLED(0,0,255);
    delay(1000);
}
