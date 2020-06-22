#include "LedPlayer.h"

LedPlayer player;

void setup(){
    player.init();
    Serial.begin(9600);
}

void loop(){
    player.run();
}
