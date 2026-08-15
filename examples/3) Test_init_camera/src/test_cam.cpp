#include <NeuroBoardS3.h>


void setup()
{
  Serial.begin(9600);
  NeuroBoard.initLED();

  if(NeuroBoard.initCamera())
    NeuroBoard.setLED(0,255,0);
  else
    NeuroBoard.setLED(255,0,0);
}

void loop(){}
