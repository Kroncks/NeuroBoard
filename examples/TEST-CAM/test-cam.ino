#include <NeuroBoard.h>


void setup()
{
    NeuroBoard.begin();

    if(NeuroBoard.initCamera())
      NeuroBoard.setRGB(0,255,0);
    else
      NeuroBoard.setRGB(255,0,0);
}

void loop(){}