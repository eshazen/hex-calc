//
// tty version of calculator, preparing for port to Arduino
//

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#define CALC_TOP_MAIN

#include "calc.h"
#include "tty_helper.h"

int
main( int    argc,
      char * argv[ ] )
{
  // set some defaults
  radix = DEF_RADIX;		/* radix */
  wsize = DEF_SIZE;		/* size */
  sign = 0;			/* unsigned */
  push = 0;

  tty_raw();

  while (1) {
    while( !tty_ready())
      ;
    int c = tty_char();
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
    if (c == 3) break;
  }

  return 0;
}
