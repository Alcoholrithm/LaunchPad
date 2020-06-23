#include "LedPlayer.h"

void pattern1(uint8_t& button, uint8_t *color)
{
    /*
        첫번째 패턴 : 십자가
    */
    uint8_t row = button / pin::num_led_rows;
    uint8_t col = button % pin::num_led_rows;

    button = 99;//initialize

    for (int j = 0; j < 4&&button==99; j++)
    {
        if (j == 0)
        {
            pre_time = millis();
            curr_time = millis();
            while (curr_time - pre_time < 100 && button == 99)
            {
              curr_time = millis();
              digitalWrite(pin::ledselpins[col + j], LOW);
              pattern_::led(row, col, ON, color);
              pattern_::led(row, col, OFF, color);
              digitalWrite(pin::ledselpins[col + j], HIGH);
            }
        }
        else
        {
            pre_time = millis();
            curr_time = millis();
            while (curr_time - pre_time < 100&& button==99)
            {
                curr_time = millis();
                if (col + j < pin::num_led_columns && col + j >= 0)
                { // row +
                    digitalWrite(pin::ledselpins[col + j], LOW);
                    pattern_::led(row, col + j, ON, color);
                    pattern_::led(row, col + j, OFF, color);
                    digitalWrite(pin::ledselpins[col + j], HIGH);
                }
                if (col - j < pin::num_led_columns && col - j >= 0)
                { // row -
                    digitalWrite(pin::ledselpins[col - j], LOW);
                    pattern_::led(row, col - j, ON, color);
                    pattern_::led(row, col - j, OFF, color);
                    digitalWrite(pin::ledselpins[col - j], HIGH);
                }
                if (col < pin::num_led_columns && col >= 0)
                { // col
                    digitalWrite(pin::ledselpins[col], LOW);
                    pattern_::led(row + j, col, ON, color);
                    pattern_::led(row - j, col, ON, color);
                    pattern_::led(row + j, col, OFF, color);
                    pattern_::led(row - j, col, OFF, color);
                    digitalWrite(pin::ledselpins[col], HIGH);
                }
            }
        }
    }
}
