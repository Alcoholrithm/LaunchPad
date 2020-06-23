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
    initTimer1();
    send_max_pattern();
    myPattern[0].pattern = pattern1;  // 패턴 지정
    myPattern[0].init(150, 150, 150); //색상 지정
    myPattern[1].pattern = pattern2;  // 패턴 지정
    myPattern[1].init(150, 150, 150); //색상 지정
    curr_pattern = 1; //테스트 코드, 출력하고 싶은 패턴으로
}

void LedPlayer::operator()(uint8_t& button)
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

ISR(TIMER1_OVF_vect) //Timer1 Service
{
    /*
        if serail available -> read serial and renew player.button
        if button == 3 -> player.curr_pattern+=1; player.curr_pattern%=player.max_pattern;
    */

}


#define RESOLUTION 65536        // Timer1 is 16 bit
void LedPlayer::initTimer1(void) //initialize Timer1 to 100us overflow
{
    TCCR1A = 0;          // clear control register A
    TCCR1B = _BV(WGM13); // set mode as phase and frequency correct pwm, stop the timer

    long cycles;
    long microseconds = 500; //setup microseconds here
    unsigned char clockSelectBits;
    cycles = (F_CPU / 2000000) * microseconds; // the counter runs backwards after TOP, interrupt is at BOTTOM so divide microseconds by 2
    if (cycles < RESOLUTION)
        clockSelectBits = _BV(CS10); // no prescale, full xtal
    else if ((cycles >>= 3) < RESOLUTION)
        clockSelectBits = _BV(CS11); // prescale by /8
    else if ((cycles >>= 3) < RESOLUTION)
        clockSelectBits = _BV(CS11) | _BV(CS10); // prescale by /64
    else if ((cycles >>= 2) < RESOLUTION)
        clockSelectBits = _BV(CS12); // prescale by /256
    else if ((cycles >>= 2) < RESOLUTION)
        clockSelectBits = _BV(CS12) | _BV(CS10); // prescale by /1024
    else
        cycles = RESOLUTION - 1, clockSelectBits = _BV(CS12) | _BV(CS10); // request was out of bounds, set as maximum

    ICR1 = cycles;
    TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
    TCCR1B |= clockSelectBits; // reset clock select register, and starts the clock

    TIMSK1 = _BV(TOIE1);
    TCNT1 = 0;
    sei(); //enable global interrupt
}


/*
    button 사용 후에는 99로 초기화
    button이 99면 패턴 호출 x
    패턴이 진행중일때에도 button이 계속 99인지 체크하고 아니면 바로 종료
*/
unsigned long long pre_time,curr_time;
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

void pattern2(uint8_t& button, uint8_t *color)
{
    /*
        두번째 패턴 : 엑스
    */
    uint8_t row = button / pin::num_led_rows;
    uint8_t col = button % pin::num_led_rows;

    button = 99; //initialize

    for (int j = 0; j < 4&&button == 99; j++)
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
            while (curr_time - pre_time < 100 && button == 99)
            {
                curr_time = millis();
                if (col + j < pin::num_led_columns && col + j >= 0)
                { // row +
                    digitalWrite(pin::ledselpins[col + j], LOW);
                    pattern_::led(row + j, col + j, ON, color);
                    pattern_::led(row - j, col + j, ON, color);
                    pattern_::led(row + j, col + j, OFF, color);
                    pattern_::led(row - j, col + j, OFF, color);
                    digitalWrite(pin::ledselpins[col + j], HIGH);
                }
                if (col - j < pin::num_led_columns && col - j >= 0)
                { // row -
                    digitalWrite(pin::ledselpins[col - j], LOW);
                    pattern_::led(row + j, col - j, ON, color);
                    pattern_::led(row - j, col - j, ON, color);
                    pattern_::led(row + j, col - j, OFF, color);
                    pattern_::led(row - j, col - j, OFF, color);
                    digitalWrite(pin::ledselpins[col - j], HIGH);
                }
                if (col < pin::num_led_columns && col >= 0)
                { // col

                }
            }
        }
    }
}
