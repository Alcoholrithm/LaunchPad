#include "LedPlayer.h"

void LedPlayer::init()
{
    /*
        led 핀 초기화
        uart통신으로 max_pattern 넘겨줌.
    */
    for (uint8_t i = 0; i < pin::num_led_columns; ++i)
    {
        pinMode(pin::ledselpins[i], OUTPUT);
        digitalWrite(pin::ledselpins[i], HIGH);
    }

    for (uint8_t i = 0; i < pin::num_led_columns; ++i)
    {
        for (uint8_t j = 0; j < 3; ++j)
        {
            pinMode(pin::ledcolorpins[i][j], OUTPUT);
            digitalWrite(pin::ledcolorpins[i][j], LOW);
        }
    }

    myPattern[0].pattern = pattern1;  // 패턴 지정
    myPattern[0].init(150, 150, 150); //색상 지정
}

void LedPlayer::operator()(const uint8_t button)
{
    /*
        pattern[button]()을 호출
    */
    myPattern[curr_pattern](button, myPattern[curr_pattern].color); //pattern operator()
}

void LedPlayer::run(void)
{
    /*
        loop안에서 돌아가는 함수
        시리얼 통신을 통해 눌러진 버튼 값을 받고 정해진 패턴으로 출력하는 pattern[button]()을 호출;
    */
    for (uint8_t i = 0; i < 16; ++i)
    {
        player(i);
    }
}

void pattern1(uint8_t button, uint8_t *color)
{
    /*
        첫번째 패턴 : 십자가
    */
    uint8_t row = button / pin::num_led_rows;
    uint8_t col = button % pin::num_led_rows;

    for (int j = 0; j < 4; j++)
    {
        if (j == 0)
        {
            Serial.println("P");
            pattern_::led(row, col, ON, color);
            timer();
            pattern_::led(row, col, OFF, color);
        }
        else
        {
            pre_time = millis();
            curr_time = millis();
            while (curr_time - pre_time < 500)
            {
                curr_time = millis();
                if (col + j < pin::num_led_columns && col + j >= 0)
                {
                    digitalWrite(pin::ledselpins[col + j], LOW);
                    pattern_::led(row, col + j, ON, color);
                    digitalWrite(pin::ledselpins[col + j], HIGH);
                }
                if (col - j < pin::num_led_columns && col - j >= 0)
                {
                    digitalWrite(pin::ledselpins[col - j], LOW);
                    pattern_::led(row, col - j, ON, color);
                    digitalWrite(pin::ledselpins[col - j], HIGH);
                }
                if (col < pin::num_led_columns && col >= 0)
                {
                    digitalWrite(pin::ledselpins[col], LOW);
                    pattern_::led(row + j, col, ON, color);
                    pattern_::led(row - j, col, ON, color);
                    digitalWrite(pin::ledselpins[col], HIGH);
                }
            }
            // pattern_::led(row, col+j, ON, color);
            // pattern_::led(row, col-j, ON, color);
            // pattern_::led(row+j, col, ON, color);
            // pattern_::led(row-j, col, ON, color);
            // timer();
            // pattern_::led(row, col+j, OFF, color);
            // pattern_::led(row, col-j, OFF, color);
            // pattern_::led(row+j, col, OFF, color);
            // pattern_::led(row-j, col, OFF, color);
        }
    }
}
