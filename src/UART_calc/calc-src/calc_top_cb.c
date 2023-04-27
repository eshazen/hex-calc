#include <stdio.h>

#include "calc_top.h"
#include "calc.h"
#include "int_limits.h"

/* Callbacks and freeobj handles for form calc_top */

/***************************************
 ***************************************/

void cb_mode( FL_OBJECT * ob,
         long        data )
{

  // switch modes
#ifdef DEBUG
  printf("cb_mode: %ld\n", data);
#endif
  
  push = 1;

  switch( data) {

  // toggle signed mode
  case M_SIG:
    sign ^= 1;
    break;

  // set the radix
  case M_HEX:
    radix = 16;
    break;
  case M_DEC:
    radix = 10;
    break;
  case M_BIN:
    radix = 2;
    break;

  // change word size, deal with sign extend etc
  // operate on entire stack
  case M_64:
  case M_32:
  case M_16:
  case M_8:
#ifdef DEBUG
    printf("Set word size code: %ld\n", data);
#endif
    set_new_word_size( data);
    break;
  default:
    printf("Unknown mode %ld\n", data);

  }

  calc_update_display();  
}

/***************************************
 ***************************************/

void cb_digit( FL_OBJECT * ob,
         long        data )
{
  FD_calc_top *f;		/* GLOBAL struct pointer */
  char str[10];

  f = fd_calc_top;

  // if push flag is set, push the stack up and clear
  if( push) {
    push = 0;
    stack_up();
    r_display.u64 = 0;
  }

  // if clear flag is set, clear first
  if( clear) {
    clear = 0;
    r_x.u64 = 0;
  }

  // handle one digit.
  if( data < radix) {
    // for hex, binary and 64-bit word size, just
    // multiply the value by the radix and add the new digit
    if( radix == 16 || radix == 2 || wsize == 64) {
      r_x.u64 = (r_x.u64 * radix) + data;
    } else {

      // for decimal word sizes < 64...
      // what we want to do here is to see if we add the digit
      // it results in an overflow, and if so strip off the
      // highest non-zero digit so the value scrolls to the left

#ifdef DEBUG
      printf("Enter digit %ld with X=%" PRIu64 "\n", data, r_x.u64);
#endif      

      uint64_t b = r_x.u64 * radix;
      uint64_t r = b + data;
      
      if( sign) {
	while( r > MAX_SIGNED(wsize)) {
#ifdef DEBUG
	  printf("signed compare %" PRIu64 " with %" PRIu64 "\n", r, MAX_SIGNED(wsize));
#endif	    
	  b = delete_high_digit( b, radix);
	  r = b + data;
	}
      } else {
	// unsigned
	while( r > MAX_UNSIGNED(wsize)) {
#ifdef DEBUG
	  printf("unsigned compare %" PRIu64 " with %" PRIu64 "\n", r, MAX_UNSIGNED(wsize));
#endif	    
	  b = delete_high_digit( b, radix);
	  r = b + data;
	}
      }
      r_x.u64 = r;
    }
  }

  calc_update_display();
}


/***************************************
 ***************************************/

void cb_arith( FL_OBJECT * ob,
         long        data )
{
    /* Fill-in code for callback here */
#ifdef DEBUG
  printf("cb_arith: %ld\n", data);
#endif
  push = 1;

  switch( data) {
  case A_CHS:
    r_x.u64 = -((int64_t)r_x.u64);
    break;
  case A_CLR:
    r_x.u64 = 0;
    break;
  case A_SUB:
    r_y.u64 -= r_x.u64;
    stack_down_copy();
    break;
  case A_ADD:
    r_y.u64 += r_x.u64;
    stack_down_copy();
    break;
  case A_MUL:
    r_y.u64 *= r_x.u64;
    stack_down_copy();
    break;
  case A_DIV:
    r_y.u64 /= r_x.u64;
    stack_down_copy();
    break;
  }

  calc_update_display();
}


/***************************************
 ***************************************/

void cb_stack( FL_OBJECT * ob,
         long        data )
{
    /* Fill-in code for callback here */
  push = 0;
  
#ifdef DEBUG
  printf("cb_stack: %ld\n", data);
#endif
  switch( data) {
  case S_DROP:			/* roll-down */
    stack_down();
    break;
  case S_PUSH:			/* ENTER */
    stack_up();
    clear = 1;			/* set flag to clear on next entry */
    break;
  case S_SWAP:			/* X/Y */
    r_temp = r_x;
    r_x = r_y;
    r_y = r_temp;
    break;
  }

  calc_update_display();
}


