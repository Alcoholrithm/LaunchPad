
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SD.h>
#include "pin.h"
#include "vs10xx.h"
#include "myList.h"
#include "button.h"
#include <avr/pgmspace.h>

#define MaxVol 250
#define MinVol 100

enum player_state
{
    IDLE = 0,
    PLAY,
    PAUSE,
};

/*****************class for the music player*******************/
class myPlayer
{
    //int Vol = 100;
    songInfo songs;
    void initIO();
    void initSD();
    void initTimer1();

public:
    button_ button;
    volatile uint16_t input = 99;
    volatile player_state state = IDLE;
    void begin();
    void play(uint16_t);
    void run();
};

extern myPlayer player;
#endif
