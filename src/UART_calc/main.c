/*
 * very simple 4-function decimal calculator to test low-level stuff
 * should work on AVR or desktop
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdlib.h>

//---- set up for character-by-character I/O ----

#ifdef AVR
#include <util/delay.h>
#include <avr/io.h>
#include "uart.h"
// Arduino LED is on PB5
#define LED_DDR DDRB
#define LED_BIT 5
#define LED_PORT PORTB
// create a file pointer for read/write to USART0
FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);

#define tty_ready() USART0CharacterAvailable()
#define tty_char() USART0ReceiveByte(NULL)

#else

#include "calc-src/tty_helper.h"

#endif
//-------------------------------------------------

// buffer for converted values for printing
static char sval[21];
// the stack
static int64_t x, y, z;

// convert uint64 to string (from KamilCuk on stackoverflow)
char *uint64_to_str(uint64_t n, char dest[21] ) {
  dest += 20;
  *dest-- = 0;
  while (n) {
    *dest-- = (n % 10) + '0';
    n /= 10;
  }
  return dest + 1;
}

static int c;
char *op;
char *val;

int main (void)
{

  //---- initialize character-by-character input mode ----
#ifdef AVR
  USART0Init();
  stdout = &usart0_str;		/* connect UART to stdout */
  stdin = &usart0_str;		/* connect UART to stdin */

  LED_DDR ^= (1 << LED_BIT);
#else
  tty_raw();
#endif
  
  puts("UART test");

  while( 1) {

    // collect characters and process them
    c = tty_char();
#ifndef AVR
    if( c == 3)
      exit(1);
#endif    

    if( isxdigit(c)) {
      if( isdigit(c))
	c -= '0';
      else
	c -= toupper(c) - 'A' + 1;
      x = x * 10LL + c;

    } else if( (op = strchr( "+-*/", c))) {

      switch( *op) {
      case '+':
	x = x + y;
	break;
      case '-':
	x = y - x;
	break;
      case '*':
	x = x * y;
	break;
      case '/':
	x = y / x;
	break;
      }
      
    } else if( c == 13 || c == 10) {
      z = y;
      y = x;
      x = 0;
    }

    // update display
    val = uint64_to_str( z, sval);
    printf("Z: %s\n", val);
    val = uint64_to_str( y, sval);
    printf("Y: %s\n", val);
    val = uint64_to_str( x, sval);
    printf("X: %s\n", val);
    puts( "----");
  }
}


