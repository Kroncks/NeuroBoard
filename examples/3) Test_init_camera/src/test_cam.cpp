#include <NeuroBoard.h>


void setup()
{
    Serial.begin(9600);
NeuroBoard.initRGB();

    if(NeuroBoard.initCamera())
      NeuroBoard.setRGB(0,255,0);
    else
      NeuroBoard.setRGB(255,0,0);
}

void loop(){}
