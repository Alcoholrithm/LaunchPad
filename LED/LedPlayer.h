#ifndef PLAYER_H_
#define PLAYER_H_

#include "pattern.h"
#include <SoftwareSerial.h>

class LedPlayer
{
public:
    uint8_t curr_pattern = 0;
    static const uint8_t max_pattern = 3; //패턴의 경우의 수 저장.
    uint8_t button = 99;                  //사용 후 반드시 99로 초기화해주기
    void init();                          //uart 통신을 통해서 max_pattern을 myPlayer로 넘겨줌. //setup에서 호출
    void run(void);                       //loop안에서 돌아가는 함수
private:
    pattern_ myPattern[max_pattern];

    void operator()(uint8_t&); //인자로 들어오는 패턴을 호출;
    void initTimer1(void);
    void send_max_pattern(void){}//시작시 시리얼로 max_pattern 전송해줌.
};

extern void pattern1(uint8_t&, uint8_t*); // 십자가
extern void pattern2(uint8_t&, uint8_t*); // 엑스
extern void pattern3(uint8_t&, uint8_t*); // 원형
extern LedPlayer player;
extern unsigned long long pre_time, curr_time;
extern uint8_t input;

#endif
