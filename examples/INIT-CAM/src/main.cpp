#include <NeuroBoard.h>


void setup()
{
    Serial.begin(115200);


    NeuroBoard.begin();


    if(NeuroBoard.initCamera())
    {
        NeuroBoard.setRGB(0,255,0);
    }
    else
    {
        NeuroBoard.setRGB(255,0,0);
    }

}


void loop()
{

}