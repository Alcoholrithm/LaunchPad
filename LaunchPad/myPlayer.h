
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SD.h>
#include "pin.h"
#include "vs10xx.h"
#include "myList.h"
#include "button.h"
#include "lcd.h"
#include <SoftwareSerial.h>

enum player_state
{
    IDLE = 0,
    PLAY,
    PAUSE,
};

/*****************class for the music player*******************/
class myPlayer
{
    static const uint8_t maxVol = 0;
    static const uint8_t minVol = 100;
    static const uint8_t mute = 200;
    uint8_t Vol = 100; //작을 수록 소리가 큼.
    uint16_t pre_resist;
    trackInfo tracks;
    void initIO(void);
    void initSD(void);
    void initTimer1(void);
    uint8_t current_pattern;
    uint8_t max_pattern;
    void setVol(void);
    LCD lcd;
    void next_pattern(void);
public:
    button_ button;
    volatile uint16_t resist;
    volatile uint16_t input = 99;
    volatile player_state state = IDLE;
    void init(void);
    void play(uint16_t);
    void run(void);
};

extern myPlayer player;
#endif
