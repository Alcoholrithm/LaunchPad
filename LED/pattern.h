#ifndef _PATTERN_H_
#define _PATTERN_H_

#include "pin.h"

enum state_
{
    OFF = 0,
    ON,
};
enum SIG{
        RESET,
        INCREASE,
    };
class pattern_
{
    uint8_t color[3];                //패턴마다 나타낼 색상을 저장.
    void (*pattern)(uint8_t& button, uint8_t* color); //출력 패턴대로 출력하는 함수포인터를 저장    
    static uint64_t sig; //0이 아니면 랜덤 재생, 0이면 정지, 버튼 값이 99를 넘겨받으면 0이됨.
    static uint64_t get_sig(void);
public:
    void init(const uint8_t,const uint8_t,const uint8_t);
    static void led(const uint8_t row, const uint8_t col, state_ state, uint8_t* color);     //인자로 들어간 led를 킴, state는 on, off
    void operator()(uint8_t&,uint8_t*);                 //표시할 패턴을 Led로 출력 해 줌. // pattern(uint8_t, uint8_t*)를 사용.
    void set_pattern(void (*)(uint8_t&, uint8_t*));                   //함수 포인터에 원하는 함수 저장.
    uint8_t* get_color(void);
    static void set_sig(SIG);
};

using ull = unsigned long long;
static ull pre_time;
static ull curr_time;


#endif
