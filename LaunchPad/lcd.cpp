#include "lcd.h"

void LCD::init()
{
    lcd.begin(16, 2); // LCD 크기설정
    lcd.clear();      // LCD 초기화
}

void LCD::set_pattern(uint8_t recive_pattern) // 패턴 변경사항 current_pattern에 반영
{
    current_pattern = recive_pattern;
    printLcd();
}

void LCD::set_current_track(char *recive_track) // track변경사항을 current_track에 반영
{
    strncpy(current_track, recive_track, 10);
    printLcd();
}

void LCD::printLcd() //패턴과 트랙 출력
{   
    lcd.clear();
    lcd.print(String("Track ") + current_track + "\nPattern #" + current_pattern);
}