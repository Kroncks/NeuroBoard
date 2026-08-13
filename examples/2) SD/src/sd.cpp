#include <NeuroBoard.h>


static bool writeTestFile()
{
    File file = SD_MMC.open("/test.txt", FILE_WRITE);
    if(!file) return false;

    bool ok = file.print("bonsoir") > 0;
    file.close();
    return ok;
}


void setup()
{
    Serial.begin(9600);
    NeuroBoard.initLED();

    if(!NeuroBoard.initSD())
    {
        NeuroBoard.setLED(255, 0, 0);
        return;
    }

    if(writeTestFile())
        NeuroBoard.setLED(0, 255, 0);
    else
        NeuroBoard.setLED(255, 0, 0);
}


void loop(){}
