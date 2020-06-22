#include "pattern.h"


void pattern_::led(const uint8_t row, const uint8_t col, state_ state, uint8_t* color)
{
    if(row<0 || row >= pin::num_led_rows || col < 0 || col>= pin::num_led_columns)
        return;
    digitalWrite(pin::ledselpins[col], LOW);
    if (state == ON)
    {
        for (uint8_t j = 0; j < 3; ++j)
            digitalWrite(pin::ledcolorpins[row][j], color[j]);
        Serial.println(String(row*4+col) + " on");
    }
    else
    {
        for (uint8_t j = 0; j < 3; ++j)
            digitalWrite(pin::ledcolorpins[row][j], 0);
        Serial.println(String(row * 4 + col) + " off");
    }
    digitalWrite(pin::ledselpins[col], HIGH);
}
using ull = unsigned long long;
static  ull pre_time;
static ull curr_time;

void timer(void){
        pre_time = millis();
        do
        {
            curr_time = millis();
        } while (curr_time - pre_time > 500);
}

void pattern_::init(const uint8_t R, const uint8_t G, const uint8_t B){//색상 초기화
    color[0] = R;
    color[1] = G;
    color[2] = B;
}

void pattern_::operator()(uint8_t button, uint8_t* color){
    pattern(button, color);
}
