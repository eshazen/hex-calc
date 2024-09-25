/*
 * hex calculator for target hardware
 */
#define CALC_TOP_MAIN

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "kb.h"
#include "timer.h"
#include "led.h"
#include "calc.h"
#include "calc_key.h"
#include "custom.h"

// #define DEBUG_KEY

// universal LCD display buffer
char msg[LCD_WID+2];

extern uint8_t kb_val[];

int main (void)
{
  lcd_init();
  led_init();
  kb_init();

  load_custom_char();

  timer_setup();
  sei();			/* enable interrups */

  lcd_puts( "Hex calc V0.2");
  lcd_addr( 0x40);
  for( uint8_t i=1; i<=8; i++)
    lcd_putc( i);
  

  _delay_ms( 1000);
  lcd_cls();

  // set some defaults
  radix = DEF_RADIX;		/* radix */
  wsize = DEF_SIZE;		/* size */

  sign = 0;			/* unsigned */
  push = 0;

  while( 1) {

    uint32_t ms = get_millis();

    // poll KB every 1 ms
    poll_kb();
      
    // check/update display every 256 ms
    if( !(ms & 255)) {

      int k = get_kb();

      if( k) {
#ifdef DEBUG_KEY
      // display key code
      lcd_addr( 0);
      snprintf( msg, sizeof(msg), "key: %c (%02x) ", shift ? 'S' : 'N', k);
      lcd_puts( msg);
      _delay_ms(500);
#endif
	calc_key( k);
      } // if(k)

	// set LEDs
      set_led( 0, shift);
      set_led( 1, sign);

    } // 255 ms

  }

}
