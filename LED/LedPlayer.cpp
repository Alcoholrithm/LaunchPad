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
    Serial.begin(9600);
    myPattern[0].pattern = pattern1;  // 패턴 지정
    myPattern[0].init(150, 150, 150); //색상 지정
    myPattern[1].pattern = pattern2;  // 패턴 지정
    myPattern[1].init(150, 150, 150); //색상 지정
    myPattern[2].pattern = pattern3;  // 패턴 지정
    myPattern[2].init(150, 150, 150); //색상 지정
    curr_pattern = 2;                 //테스트 코드, 출력하고 싶은 패턴으로
}

void LedPlayer::operator()(uint8_t &button)
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
    readSerial();
    if (player.button<16){
        player(player.button);
    }
    
    for (uint8_t i = 0; i < 15; i++)
    {
        uint8_t j = i;
        player(j);
    }
}

//ISR(TIMER1_OVF_vect) //Timer1 Service
//{
    /*
        if serail available -> read serial and renew player.button
        if button == 3 -> player.curr_pattern+=1; player.curr_pattern%=player.max_pattern;
    */
    /*
    if (Serial.available())
    {
        player.button = Serial.read();
        Serial.print(player.button);
        if (player.button == 3)
        {
            player.curr_pattern += 1;
            player.curr_pattern %= player.max_pattern;
        }
    }*/
//}
/*
#define RESOLUTION 65536             // Timer1 is 16 bit
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
*/
    /*
    button 사용 후에는 99로 초기화
    button이 99면 패턴 호출 x
    패턴이 진행중일때에도 button이 계속 99인지 체크하고 아니면 바로 종료
*/


void LedPlayer::readSerial(void){
    char temp[3];
    if (Serial.available()) {
        player.button=0;
        byte len = Serial.readBytesUntil('\n',temp, 3);
        for (int i = 0; i < len; i++) {
            player.button = player.button*10+temp[i]-'0';
        }
        Serial.println(player.button);
    }
    if (player.button==3){
        curr_pattern+=1;
        curr_pattern = curr_pattern%max_pattern; 
    }
}
