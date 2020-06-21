
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SD.h>
#include "pin.h"
#include "vs10xx.h"
#include "myList.h"
#include "button.h"

enum player_state
{
    IDLE = 0,
    PLAY,
    PAUSE,
};

/*****************class for the music player*******************/
class myPlayer
{
    static const uint8_t maxVol = 210;
    static const uint8_t minVol = 0;
    uint8_t Vol = 100; //작을 수록 소리가 큼.
    uint16_t pre_resist;
    songInfo songs;
    void initIO();
    void initSD();
    void initTimer1();

public:
    button_ button;
    volatile uint16_t resist;
    volatile uint16_t input = 99;
    volatile player_state state = IDLE;
    void begin();
    void play(uint16_t);
    void run();
    void setVol();
};

extern myPlayer player;
#endif
