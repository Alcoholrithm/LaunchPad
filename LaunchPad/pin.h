#ifndef PIN_H_
#define PIN_H_

#include "pins_config.h"

#include <avr/io.h>
#include <arduino.h>

////////////////////////for MMC////////////////////////////////////
#define SD_CS_PIN 53   //SD card select pin linked to pin53 of MCU

///////////////////////for vs10xx///////////////////////////////////
#define VS_XRESET A0
#define VS_DREQ   A1
#define VS_XDCS   A2
#define VS_XCS    A3

namespace pin{
    const uint8_t num_led_columns = 4;
    const uint8_t num_led_rows = 4;
    const uint8_t num_btn_columns = 4;
    const uint8_t num_btn_rows = 4;
    static const uint8_t btncolumnpins[num_btn_columns] = {2, 3, 4, 5};
    static const uint8_t btnrowpins[num_btn_rows]       = {26, 27, 28, 29};
    static const uint8_t ledcolumnpins[num_led_columns] = {42, 43, 44, 45};
    static const uint8_t colorpins[num_led_rows]        = {22, 30, 33, 36};
}
#endif
