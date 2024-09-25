#include <stdint.h>
#include "lcd.h"
#include "custom.h"

//
// define up to 8 custom characters
const uint8_t Custom_Char5x8[] = {
  0b10001,0b01110,0b01100,0b01010,0b00110,0b01110,0b10001,0b11111, // 0
  0b11011,0b10011,0b11011,0b11011,0b11011,0b11011,0b10001,0b11111, // 1
  0b10001,0b01110,0b01110,0b01110,0b00000,0b01110,0b01110,0b11111, // A
  0b00001,0b01110,0b01110,0b00001,0b01110,0b01110,0b00001,0b11111, // B
  0b10001,0b01110,0b01111,0b01111,0b01111,0b01110,0b10001,0b11111, // C
  0b00011,0b01101,0b01110,0b01110,0b01110,0b01101,0b00011,0b11111, // D
  0b00000,0b01111,0b01111,0b00001,0b01111,0b01111,0b00000,0b11111, // E
  0b00000,0b01111,0b01111,0b00001,0b01111,0b01111,0b01111,0b11111  // F
};

void load_custom_char() {
  send_ctrl( 0x04);		/* set CGRAM address */
  send_ctrl( 0x00);
  for( uint8_t i=0; i<sizeof(Custom_Char5x8); i++)
    lcd_putch( Custom_Char5x8[i]);
  send_ctrl( 0);
  send_ctrl( 2);
}
