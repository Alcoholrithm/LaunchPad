#include "LedPlayer.h"

SoftwareSerial unoSerial(18, 19); // 18(A4):RX 19(A5):TX

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
    unoSerial.begin(9600);
    myPattern[0].set_pattern(pattern1);
    myPattern[0].init(150, 150, 150); //색상 지정
    myPattern[1].set_pattern(pattern2);
    myPattern[1].init(150, 150, 150); //색상 지정
    curr_pattern = 0;                 //테스트 코드, 출력하고 싶은 패턴으로
    //send_max_pattern();
}

void LedPlayer::operator()(uint8_t &button)
{
    /*
        pattern[button]()을 호출
    */
    myPattern[curr_pattern](button, myPattern[curr_pattern].get_color()); //pattern operator()
}

void LedPlayer::run(void)
{
    /*
        loop안에서 돌아가는 함수
        시리얼 통신을 통해 눌러진 버튼 값을 받고 정해진 패턴으로 출력하는 pattern[button]()을 호출;
    */
    readSerial();
    if (player.button < 16)
    {
        Serial.print("Press button ");
        Serial.println(player.button);
        player(player.button);
    }
    /*
    for (uint8_t i = 0; i < 16; i++)
    {
        uint8_t j = i;
        player(j);
    }
    */
}
/*
    button 사용 후에는 99로 초기화
    button이 99면 패턴 호출 x
    패턴이 진행중일때에도 button이 계속 99인지 체크하고 아니면 바로 종료
*/

void LedPlayer::readSerial(void)
{

    char temp[3];
    if (unoSerial.available())
    {
        // Serial.println("asd");
        player.button = 0;
        byte len = unoSerial.readBytes(temp, 3);
        for (int i = 0; i < len; i++)
        {
            player.button = player.button * 10 + temp[i] - '0';
        }
        
        Serial.print("UART Get ");
        Serial.println(player.button);
        pattern_::set_sig(RESET);
    }
    
    if (player.button == 3)
    {
        curr_pattern += 1;
        curr_pattern = curr_pattern % max_pattern;
    }
    
}

/*void LedPlayer::send_max_pattern(void)
{
    unoSerial.print(max_pattern);
}*/
