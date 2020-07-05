#ifndef LCD_H_
#define LCD_H_

#include <LiquidCrystal.h>
//  핀 번호        RS  E   D4  D5  D6  D7
LiquidCrystal lcd(44, 45, 46, 47, 48, 49); // LCD

class LCD{
    uint8_t current_pattern; //myPlayer에서 current_pattern값을 받아서 저장
    char current_track[10]; // trackInfo에서 current_track값을 받아서 저장
public:
    void init(void); //lcd 초기화
    void set_pattern(uint8_t); // 패턴 변경사항 current_pattern에 반영
    void set_current_track(char*); // track변경사항을 current_track에 반영
    void printLcd(void); //패턴과 트랙 출력
};

#endif
