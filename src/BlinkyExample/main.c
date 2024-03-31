/*
 * blinky example
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

// calculator LEDs on PB0, 1

#define LED_DDR DDRB
#define LED_BIT_D1 0
#define LED_BIT_D2 1
#define LED_PORT PORTB

#define bit(b) ((1)<<(b))

int main (void)
{

  LED_DDR |= bit(LED_BIT_D1) | bit(LED_BIT_D2);

  while( 1) {
    LED_PORT |= (1 << LED_BIT_D1);
    _delay_ms( 500);
    LED_PORT &= ~(1 << LED_BIT_D1);
    _delay_ms( 500);
    LED_PORT |= (1 << LED_BIT_D2);
    _delay_ms( 500);
    LED_PORT &= ~(1 << LED_BIT_D2);
    _delay_ms( 500);
  }
}


