#ifndef PIN_H_
#define PIN_H_

#include <avr/io.h>
#include <arduino.h>
#include <SoftwareSerial.h>

namespace pin
{
    //for vs_1053
    const uint8_t vs_xreset = A0;
    const uint8_t vs_dreq = A1;
    const uint8_t vs_xdcs = A2;
    const uint8_t vs_xcs = A3;

    //SD card select pin linked to pin53 of MCU
    const uint8_t sd_cs_pin = 53; 
    // sd_sel_pin = 9;
    //for buttons
    const uint8_t num_btn_columns = 4;
    const uint8_t num_btn_rows = 4;
    const uint8_t btncolumnpins[num_btn_columns] = {2, 3, 4, 5};
    const uint8_t btnrowpins[num_btn_rows] = {26, 27, 28, 29};

    //for potentiometer
    const uint8_t resistor_pin = A6;

    //for Serial1 not using in code;
    /*
        RX = 19;
        TX - 18;
    */
} // namespace pin
#endif
