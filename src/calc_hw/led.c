
#include <avr/io.h>
#include "led.h"

void led_init() {
  LED_DDR |= _BV(LED_BIT_D1) | _BV(LED_BIT_D2);
  LED_PORT |= (_BV(LED_BIT_D1) | _BV(LED_BIT_D2));
}

void set_led( int num, int state) {
  if( num) {
    if( state)
      LED_PORT &= ~ _BV(LED_BIT_D1);
    else
      LED_PORT |= _BV(LED_BIT_D1);
  } else {
    if( state)
      LED_PORT &= ~ _BV(LED_BIT_D2);
    else
      LED_PORT |= _BV(LED_BIT_D2);
  }
}
