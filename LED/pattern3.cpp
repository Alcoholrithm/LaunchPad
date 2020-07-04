#include "LedPlayer.h"

void pattern3(uint8_t& button, uint8_t *color)
{
    /*
        세번째 패턴 : 원형
    */
    uint8_t row = button / pin::num_led_rows;
    uint8_t col = button % pin::num_led_rows;

    button = 99; //initialize

    for (int j = 0; j < 4 && button == 99; j++)
    {
        player.readSerial();
        if (j == 0)
        {
            pre_time = millis();
            curr_time = millis();
            while (curr_time - pre_time < 100 && button == 99)
            { // Point
              curr_time = millis();
              digitalWrite(pin::ledselpins[col], LOW);
              pattern_::led(row, col, ON, color);
              pattern_::led(row, col, OFF, color);
              digitalWrite(pin::ledselpins[col], HIGH);
            }
        } else if (j == 1) {
            pre_time = millis();
            curr_time = millis();
            while (curr_time - pre_time < 100 && button == 99)
            {
                curr_time = millis();
                if (col + j < pin::num_led_columns && col + j >= 0)
                { // col +
                    digitalWrite(pin::ledselpins[col + j], LOW);
                    pattern_::led(row, col + j, ON, color);
                    pattern_::led(row + j, col + j, ON, color);
                    pattern_::led(row - j, col + j, ON, color);
                    pattern_::led(row, col + j, OFF, color);
                    pattern_::led(row + j, col + j, OFF, color);
                    pattern_::led(row - j, col + j, OFF, color);
                    digitalWrite(pin::ledselpins[col + j], HIGH);
                }
                if (col - j < pin::num_led_columns && col - j >= 0)
                { // col -
                    digitalWrite(pin::ledselpins[col - j], LOW);
                    pattern_::led(row, col - j, ON, color);
                    pattern_::led(row + j, col - j, ON, color);
                    pattern_::led(row - j, col - j, ON, color);
                    pattern_::led(row, col - j, OFF, color);
                    pattern_::led(row + j, col - j, OFF, color);
                    pattern_::led(row - j, col - j, OFF, color);
                    digitalWrite(pin::ledselpins[col - j], HIGH);
                }
                if (col < pin::num_led_columns && col >= 0)
                { // row
                    digitalWrite(pin::ledselpins[col], LOW);
                    pattern_::led(row + j, col, ON, color);
                    pattern_::led(row - j, col, ON, color);
                    pattern_::led(row + j, col, OFF, color);
                    pattern_::led(row - j, col, OFF, color);
                    digitalWrite(pin::ledselpins[col], HIGH);
                }
            }
        } else if (j == 2) {
            pre_time = millis();
            curr_time = millis();
            while (curr_time - pre_time < 100 && button == 99)
            {
                curr_time = millis();
                if (col + j - 1 < pin::num_led_columns && col + j - 1 >= 0)
                { // col +1
                    digitalWrite(pin::ledselpins[col + j - 1], LOW);
                    pattern_::led(row + j, col + j - 1, ON, color);
                    pattern_::led(row - j, col + j - 1, ON, color);
                    pattern_::led(row + j, col + j - 1, OFF, color);
                    pattern_::led(row - j, col + j - 1, OFF, color);
                    digitalWrite(pin::ledselpins[col + j - 1], HIGH);
                }
                if (col + j < pin::num_led_columns && col + j >= 0)
                { // col +2
                    digitalWrite(pin::ledselpins[col + j], LOW);
                    pattern_::led(row, col + j, ON, color);
                    pattern_::led(row + j, col + j, ON, color);
                    pattern_::led(row + 1, col + j, ON, color);
                    pattern_::led(row - 1, col + j, ON, color);
                    pattern_::led(row - j, col + j, ON, color);
                    pattern_::led(row, col + j, OFF, color);
                    pattern_::led(row + j, col + j, OFF, color);
                    pattern_::led(row + 1, col + j, OFF, color);
                    pattern_::led(row - 1, col + j, OFF, color);
                    pattern_::led(row - j, col + j, OFF, color);
                    digitalWrite(pin::ledselpins[col + j], HIGH);
                }
                if (col - j + 1 < pin::num_led_columns && col - j + 1 >= 0)
                { // col -1
                    digitalWrite(pin::ledselpins[col - j + 1], LOW);
                    pattern_::led(row - j, col - j + 1, ON, color);
                    pattern_::led(row + j, col - j + 1, ON, color);
                    pattern_::led(row - j, col - j + 1, OFF, color);
                    pattern_::led(row + j, col - j + 1, OFF, color);
                    digitalWrite(pin::ledselpins[col - j + 1], HIGH);
                }
                if (col - j < pin::num_led_columns && col - j >= 0)
                { // col -2
                    digitalWrite(pin::ledselpins[col - j], LOW);
                    pattern_::led(row, col - j, ON, color);
                    pattern_::led(row + j, col - j, ON, color);
                    pattern_::led(row + 1, col - j, ON, color);
                    pattern_::led(row - 1, col - j, ON, color);
                    pattern_::led(row - j, col - j, ON, color);
                    pattern_::led(row, col - j, OFF, color);
                    pattern_::led(row + j, col - j, OFF, color);
                    pattern_::led(row + 1, col - j, OFF, color);
                    pattern_::led(row - 1, col - j, OFF, color);
                    pattern_::led(row - j, col - j, OFF, color);                    
                    digitalWrite(pin::ledselpins[col - j], HIGH);
                }
                if (col < pin::num_led_columns && col >= 0)
                { // row
                    digitalWrite(pin::ledselpins[col], LOW);
                    pattern_::led(row + j, col, ON, color);
                    pattern_::led(row - j, col, ON, color);
                    pattern_::led(row + j, col, OFF, color);
                    pattern_::led(row - j, col, OFF, color);
                    digitalWrite(pin::ledselpins[col], HIGH);
                }
            }
        } else if (j == 3) {
            pre_time = millis();
            curr_time = millis();
            while (curr_time - pre_time < 100 && button == 99)
            {
                curr_time = millis();
                if (col + j - 2 < pin::num_led_columns && col + j - 2 >= 0)
                { // col +1
                    digitalWrite(pin::ledselpins[col + j - 2], LOW);
                    pattern_::led(row + j, col + j - 2, ON, color);
                    pattern_::led(row - j, col + j - 2, ON, color);
                    pattern_::led(row + j, col + j - 2, OFF, color);
                    pattern_::led(row - j, col + j - 2, OFF, color);
                    digitalWrite(pin::ledselpins[col + j - 2], HIGH);
                }
                if (col + j - 1 < pin::num_led_columns && col + j - 1 >= 0)
                { // col +2
                    digitalWrite(pin::ledselpins[col + j - 1], LOW);
                    pattern_::led(row - j, col + j - 1, ON, color);
                    pattern_::led(row + j, col + j - 1, ON, color);
                    pattern_::led(row - j, col + j - 1, OFF, color);
                    pattern_::led(row + j, col + j - 1, ON, color);
                    digitalWrite(pin::ledselpins[col + j - 1], HIGH);
                }
                if (col + j < pin::num_led_columns && col + j >= 0)
                { // col +3
                    digitalWrite(pin::ledselpins[col + j], LOW);
                    pattern_::led(row, col + j, ON, color);
                    pattern_::led(row + 1, col + j, ON, color);
                    pattern_::led(row + 2, col + j, ON, color);
                    pattern_::led(row + j, col + j, ON, color);
                    pattern_::led(row - 1, col + j, ON, color);
                    pattern_::led(row - 2, col + j, ON, color);
                    pattern_::led(row - j, col + j, ON, color);
                    pattern_::led(row, col + j, OFF, color);
                    pattern_::led(row + 1, col + j, OFF, color);
                    pattern_::led(row + 2, col + j, OFF, color);
                    pattern_::led(row + j, col + j, OFF, color);
                    pattern_::led(row - 1, col + j, OFF, color);
                    pattern_::led(row - 2, col + j, OFF, color);
                    pattern_::led(row - j, col + j, OFF, color);                    
                    digitalWrite(pin::ledselpins[col + j], HIGH);
                }
                if (col - j + 2 < pin::num_led_columns && col - j + 2 >= 0)
                { // col -1
                    digitalWrite(pin::ledselpins[col - j + 2], LOW);
                    pattern_::led(row + j, col - j + 2, ON, color);
                    pattern_::led(row - j, col - j + 2, ON, color);
                    pattern_::led(row + j, col - j + 2, OFF, color);
                    pattern_::led(row - j, col - j + 2, OFF, color);
                    digitalWrite(pin::ledselpins[col - j + 2], HIGH);
                }
                if (col - j + 1 < pin::num_led_columns && col - j + 1 >= 0)
                { // col -2
                    digitalWrite(pin::ledselpins[col - j + 1], LOW);
                    pattern_::led(row + j, col - j + 1, ON, color);
                    pattern_::led(row - j, col - j + 1, ON, color);
                    pattern_::led(row + j, col - j + 1, OFF, color);
                    pattern_::led(row - j, col - j + 1, OFF, color);
                    digitalWrite(pin::ledselpins[col - j + 1], HIGH);
                }
                if (col - j < pin::num_led_columns && col - j >= 0)
                { // col -3
                    digitalWrite(pin::ledselpins[col - j], LOW);
                    pattern_::led(row, col - j, ON, color);
                    pattern_::led(row + 1, col - j, ON, color);
                    pattern_::led(row + 2, col - j, ON, color);
                    pattern_::led(row + j, col - j, ON, color);
                    pattern_::led(row - 1, col - j, ON, color);
                    pattern_::led(row - 2, col - j, ON, color);
                    pattern_::led(row - j, col - j, ON, color);
                    pattern_::led(row, col - j, OFF, color);
                    pattern_::led(row + 1, col - j, OFF, color);
                    pattern_::led(row + 2, col - j, OFF, color);
                    pattern_::led(row + j, col - j, OFF, color);
                    pattern_::led(row - 1, col - j, OFF, color);
                    pattern_::led(row - 2, col - j, OFF, color);
                    pattern_::led(row - j, col - j, OFF, color);
                    digitalWrite(pin::ledselpins[col - j], HIGH);
                }
                if (col < pin::num_led_columns && col >= 0)
                { // row
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
