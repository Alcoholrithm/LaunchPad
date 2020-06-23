#ifndef _PATTERN_H_
#define _PATTERN_H_

#include "pin.h"

enum state_
{
    OFF = 0,
    ON,
};

class pattern_
{


public:
    uint8_t color[3];                //패턴마다 나타낼 색상을 저장.
    void (*pattern)(uint8_t& button, uint8_t* color); //출력 패턴대로 출력하는 함수포인터를 저장
    void init(const uint8_t,const uint8_t,const uint8_t);
                  //curr_time과 pre_time비교.
    static void led(const uint8_t row, const uint8_t col, state_ state, uint8_t* color);     //인자로 들어간 led를 킴, state는 on, off
    void operator()(uint8_t,uint8_t*);                 //표시할 패턴을 Led로 출력 해 줌. // pattern(uint8_t, uint8_t*)를 사용.
    void set_pattern(void);                   //함수 포인터에 원하는 함수 저장.
};


#endif
