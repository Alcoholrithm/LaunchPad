#ifndef PLAYER_H_
#define PLAYER_H_

#include "pattern.h"
#include <SoftwareSerial.h>

class LedPlayer{
    static const uint8_t max_pattern = 1;//패턴의 경우의 수 저장.
    pattern_ myPattern[max_pattern];
    uint8_t curr_pattern = 0;
    void operator()(const uint8_t);//인자로 들어오는 패턴을 호출;
public:
    void init();//uart 통신을 통해서 max_pattern을 myPlayer로 넘겨줌. //setup에서 호출
    void run(void); //loop안에서 돌아가는 함수
    ~LedPlayer(){}
};

extern void pattern1(uint8_t, uint8_t*);
extern void pattern2(uint8_t, uint8_t*);
extern LedPlayer player;
extern unsigned long long pre_time, curr_time;

#endif
