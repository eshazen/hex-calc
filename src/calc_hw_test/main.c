/*
 * calculator hardware test
 *
 * display test message for 2 seconds on LCD
 * scan keyboard and display scan codes as buttons hit
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
extern uint8_t kb_diff[];
extern uint8_t kb_hits[];
extern uint16_t kb_test_hit;

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
      
      // check/update display every 256 ms
      if( !(ms & 255)) {

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

      } // 255 ms


    }

  }

}
