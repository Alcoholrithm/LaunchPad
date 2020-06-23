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

void pattern_::operator()(uint8_t button, uint8_t *color)
{
    pattern(button, color);
}
