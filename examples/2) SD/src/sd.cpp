#include <NeuroBoardS3.h>


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
        NeuroBoard.setLED(255, 165, 0); // orange
        return;
    }

    if(writeTestFile())
        NeuroBoard.setLED(0, 255, 0); // vert
    else
        NeuroBoard.setLED(255, 0, 0); // rouge
}


void loop(){}
