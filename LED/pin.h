#ifndef PIN_H_
#define PIN_H_

#include <avr/io.h>
#include <arduino.h>


namespace pin
{
    //for leds
    const uint8_t num_led_columns = 4;
    const uint8_t num_led_rows = 4;
    const uint8_t ledselpins[num_led_columns] = {50,51,52,53};
    const uint8_t ledcolorpins[num_led_columns][3] ={
        {22,23,24},
        {28,29,30},
        {34,35,36},
        {40,41,42} 
    };
    //for serial not using in code;
    /*
        RX = 19;
        TX = 18;
    */

} // namespace pin
#endif
