//
// Calculator top, currently runs on unix using tty
// or AVR using UART
//

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#define CALC_TOP_MAIN

#include "calc.h"
#include "calc_key.h"

//---- set up for character-by-character I/O ----
#ifdef AVR

#include "../uart.h"
#include "../avr_helper.h"

// create a file pointer for read/write to USART0
FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);

#define tty_ready() USART0CharacterAvailable()
#define tty_char() USART0ReceiveByte(NULL)

#else

#include "calc-src/tty_helper.h"

#endif
//-------------------------------------------------


int
main( int    argc,
      char * argv[ ] )
{
  // set some defaults
  radix = DEF_RADIX;		/* radix */
  wsize = DEF_SIZE;		/* size */
  sign = 0;			/* unsigned */
  push = 0;

  //---- initialize character-by-character input mode ----
#ifdef AVR
  USART0Init();
  stdout = &usart0_str;		/* connect UART to stdout */
  stdin = &usart0_str;		/* connect UART to stdin */
#else
  tty_raw();
#endif

  printf("Calc 0.1\n");

  while (1) {
    int c = tty_char();
#ifndef AVR
    if (c == 3) break;
#endif
    calc_key( c);
  }

  return 0;
}
