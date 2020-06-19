#ifndef BUTTON_H_
#define BUTTON_H_

#include "pin.h"
class button_
{
    uint8_t debounce_count[pin::num_btn_columns][pin::num_btn_rows]{
        0,
    };
    const uint8_t max_debounce = 3;

public:
    void init();
    volatile void scan(int *input);
};

#endif