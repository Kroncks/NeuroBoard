#include <NeuroBoard.h>


static bool writeTestFile()
{
    File file = SD_MMC.open("/test.txt", FILE_WRITE);
    if(!file)
    {
        return false;
    }

    bool ok = file.print("bonsoir") > 0;
    file.close();
    return ok;
}


void setup()
{
    NeuroBoard.begin();

    if(!NeuroBoard.initSD())
    {
        NeuroBoard.setRGB(255, 0, 0);
        return;
    }

    if(writeTestFile())
    {
        NeuroBoard.setRGB(0, 255, 0);
    }
    else
    {
        NeuroBoard.setRGB(255, 0, 0);
    }
}


void loop()
{
}