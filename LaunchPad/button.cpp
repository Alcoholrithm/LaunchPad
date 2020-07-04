#include "button.h"

void button_::init()
{
    uint8_t i;

    // initialize
    for (i = 0; i < pin::num_btn_columns; i++)
    {
        pinMode(pin::btncolumnpins[i], OUTPUT);
        // with nothing selected by default
        digitalWrite(pin::btncolumnpins[i], HIGH);
    }

    for (i = 0; i < pin::num_btn_rows; i++)
    {
        pinMode(pin::btnrowpins[i], INPUT_PULLUP);
    }
}

volatile void button_::scan(int *input)
{
    /*
        동시 입력은 없다고 가정.
        첫번째 row부터 순차적으로 탐색
     */
    for (uint8_t curr_row = 0; curr_row < 4; ++curr_row)
    {
        digitalWrite(pin::btncolumnpins[curr_row], LOW); // -> row 선택
        for (uint8_t j = 0; j < pin::num_btn_rows; ++j)
        {
            uint8_t val = digitalRead(pin::btnrowpins[j]); // 버튼 값 읽기
            if (val == LOW)
            {
                if (debounce_count[curr_row][j] < max_debounce)
                {
                    debounce_count[curr_row][j]++;
                    if (debounce_count[curr_row][j] == max_debounce)
                    { //버튼 눌러짐
                        Serial.print("Key Down ");
                        Serial.println((curr_row * pin::num_btn_rows) + j);
                    }
                }
            }
            else
            {
                if (debounce_count[curr_row][j] > 0)
                {
                    debounce_count[curr_row][j]--;
                    if (debounce_count[curr_row][j] == 0)
                    { //버튼 떼짐
                        Serial.print("Key Up ");
                        Serial.println((curr_row * pin::num_btn_rows) + j);
                        *input = curr_row * pin::num_btn_rows + j;
                        Serial.print(*input);
                    }
                }
            }
        }
        digitalWrite(pin::btncolumnpins[curr_row], HIGH);
    }
}
