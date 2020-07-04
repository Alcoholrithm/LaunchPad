#include "pattern.h"

void pattern_::led(const uint8_t row, const uint8_t col, state_ state, uint8_t *color)
{
    if (row < 0 || row >= pin::num_led_rows || col < 0 || col >= pin::num_led_columns)
        return;
    if (state == ON)
    {
        for (uint8_t j = 0; j < 3; ++j)
            digitalWrite(pin::ledcolorpins[row][j], color[j]);
    }
    else
    {
        for (uint8_t j = 0; j < 3; ++j)
            digitalWrite(pin::ledcolorpins[row][j], 0);
    }
}

void pattern_::init(const uint8_t R, const uint8_t G, const uint8_t B)
{ //색상 초기화
    color[0] = R;
    color[1] = G;
    color[2] = B;
}

uint8_t* pattern_::get_color(void){
    return color;
} 

void pattern_::set_pattern(void (*p)(uint8_t&, uint8_t*)){
    pattern = p;  
}

uint64_t pattern_::sig = 0;
void pattern_::operator()(uint8_t &button, uint8_t *color)
{
    set_sig(INCREASE);
    do
    {
        Serial.print(button);
        Serial.print(' ');
        pattern(button, color);
        if (get_sig())
            button = random(16);
    } while (get_sig());
}

void pattern_::set_sig(SIG state)
{
    if (state == RESET)
    {
        sig = 0;
    }
    else
    {
        ++sig;
    }
}

uint64_t pattern_::get_sig(void)
{
    return sig;
}
