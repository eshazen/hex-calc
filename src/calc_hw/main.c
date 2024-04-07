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

// universal LCD display buffer
char msg[17];

extern uint8_t kb_val[];

int main (void)
{
  lcd_init();
  led_init();
  kb_init();

  load_custom_char();

  timer_setup();
  sei();			/* enable interrups */

  lcd_puts( "Hex calc V0.1");
  lcd_addr( 0x40);
  for( uint8_t i=1; i<=8; i++)
    lcd_putc( i);
  

  _delay_ms( 1000);
  lcd_cls();

  // set some defaults
  //  radix = DEF_RADIX;		/* radix */
  //  wsize = DEF_SIZE;		/* size */

  // debug
  radix = 16;
  wsize = 16;

  sign = 0;			/* unsigned */
  push = 0;

  while( 1) {

    uint32_t ms = get_millis();

    // poll KB every 1 ms
    //    if( !(ms & 7)) {
      poll_kb();
      
      // check/update display every 256 ms
      if( !(ms & 255)) {

	int k = get_kb();
	if( k) {
	  calc_key( k);
	} // if(k)

	// set LEDs
	set_led( 0, shift);
	set_led( 1, sign);

      } // 255 ms


      //    }

  }

}
