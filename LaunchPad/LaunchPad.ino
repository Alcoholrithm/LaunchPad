#include <SPI.h>
#include <SD.h>
#include "myPlayer.h"
#include "pin.h"

myPlayer player;

void setup()
{
    Serial.begin(115200);
    player.begin();
}

void loop()
{
    player.run();
}
