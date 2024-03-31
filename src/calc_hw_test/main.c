/*
 * calculator hardware test
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "kb.h"
#include "timer.h"
#include "led.h"


static char msg[17];

extern uint8_t kb_val[];

int main (void)
{
  io_init();
  LED_DDR |= _BV(LED_BIT_D1) | _BV(LED_BIT_D2);
  LED_PORT &= ~(_BV(LED_BIT_D1) | _BV(LED_BIT_D2));

  lcd_init();
  kb_init();

  timer_setup();
  sei();			/* enable interrups */

  lcd_puts( "Calc HW Test");
  lcd_addr( 40);
  lcd_puts( "LCD Line 2");

  _delay_ms( 2000);

  while( 1) {

    uint32_t ms = get_millis();

    // poll KB every 8 ms
    if( !(ms & 7)) {
      poll_kb();

      // check/update display every 64 ms
      if( !(ms & 63)) {

	int k = get_kb();
      
	if( k) {
	  lcd_cls();
	  switch( k) {
	  case 0x27:		/* enter key */
	    lcd_puts("        DEADBEEF");
	    lcd_addr( 40);
	    lcd_puts("HEX 32 UNS");
	    break;

	  case 1:			/* upper left key */
	    ms = get_millis();
	    snprintf( msg, sizeof(msg), "us=%ld ", ms);
	    lcd_puts( msg);
	    break;

	  default:			/* just display keycode */
	    lcd_addr( 0);
	    snprintf( msg, sizeof(msg), "%04x ", k);
	    lcd_puts( msg);
	  } // switch()
	} // if(k)

      } // 63 ms

      // every 256 ms
      if( !(ms & 255)) {
	lcd_addr( 40);
	snprintf( msg, sizeof(msg), "%02x %02x %02x %02x",
		  kb_val[0], kb_val[1], kb_val[2], kb_val[3]);
	lcd_puts( msg);
      }

    } // 7 ms

  }

}
