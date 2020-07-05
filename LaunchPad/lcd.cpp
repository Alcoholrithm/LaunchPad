#include "lcd.h"

void LCD::init()
{
    lcd.begin(16, 2); // LCD 크기설정
    lcd.clear();      // LCD 초기화
}

void LCD::set_pattern(uint8_t recive_pattern) // 패턴 변경사항 current_pattern에 반영
{
    current_pattern = recive_pattern;
}
    
void LCD::set_current_track(char* recive_track) // track변경사항을 current_track에 반영
{
    current_track = recive_track;
}

void LCD::printLcd() //패턴과 트랙 출력
{
    lcd.setCursor(0, 0);
    lcd.print(current_track);

    lce.setCursor(0, 1);
    lcd.print("Pattern : ");
    lcd.print(current_pattern);
}