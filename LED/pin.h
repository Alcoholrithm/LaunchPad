#ifndef PIN_H_
#define PIN_H_

#include <avr/io.h>
#include <arduino.h>


namespace pin
{
    //for leds
    const uint8_t num_led_columns = 4;
    const uint8_t num_led_rows = 4;
    const uint8_t ledselpins[num_led_columns] = {A0,A1,A2,A3};
    const uint8_t ledcolorpins[num_led_columns][3] ={
        {2,3,4},
        {5,6,7},
        {8,9,10},
        {11,12,13}
    };
    //for serial not using in code;
    /*
        RX = 1;
        TX = 0;
    */

} // namespace pin
#endif
