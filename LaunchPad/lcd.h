#ifndef LCD_H_
#define LCD_H_

#include <LiquidCrystal.h>
#include "pin.h"

class LCD{
    uint8_t current_pattern; //myPlayer에서 current_pattern값을 받아서 저장
    char current_track[10]; // trackInfo에서 current_track값을 받아서 저장
    LiquidCrystal lcd;
    void init(void); //lcd 초기화
public:
    LCD(): lcd(pin::RS, pin::E, pin::D4, pin::D5, pin::D6, pin::D7) {
        init();
    }
    void set_pattern(uint8_t); // 패턴 변경사항 current_pattern에 반영
    void set_current_track(char*); // track변경사항을 current_track에 반영
    void printLcd(void); //패턴과 트랙 출력
};

#endif
