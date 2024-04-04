//
// perform action on key press
//
// keyboard mapping table

// #define DEBUG

#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include "calc.h"
#include "lcd.h"

// #define STATUS_KEY

extern char msg[17];

typedef struct {
  uint8_t key;
  int action_group;
  int action_code;
} a_key;

// key codes for the 16 hex digits
static uint8_t xdigits[] = { 0x17, 0x16, 0x26, 0x36, 0x15, 0x25, 0x35,
  0x14, 0x24, 0x34, 0x13, 0x23, 0x33, 0x12, 0x22, 0x32 };

// convert key code to hex digit or 0 if it isn't
uint8_t calc_xdigit( uint8_t k) {
  for( uint8_t i=0; i<sizeof(xdigits); i++) {
    if( k == xdigits[i]) {
      if( i < 10)
	return i + '0';
      else
	return i - 10 + 'A';
    }
  }
  return 0;
}


#define ctl(c) ((c)-'a'+1)

enum { KG_MODE, KG_ARITH, KG_STACK};

static a_key keys[] = {
  // real hardware, first value is key code with high bit set for shifted
  { 0xb2, KG_MODE, M_SIG },	/* toggle SIGNED display */
  { 0x01, KG_MODE, M_HEX },	/* set HEX mode */
  { 0x21, KG_MODE, M_DEC },	/* set DEC mode */
  { 0x11, KG_MODE, M_BIN },	/* set BIN mode (base Ten) */
  { 0x81, KG_MODE, M_64 },	/* set 64-bit word size (Octobyte) */
  { 0x91, KG_MODE, M_32 },	/* set 32-bit word size (Quad byte) */
  { 0xa1, KG_MODE, M_16 },	/* set 16-bit word size (Word) */
  { 0xb1, KG_MODE, M_8 },	/* set 8-bit word size (Byte) */

  { 0x02, KG_ARITH, A_CLR },	/* Clear x */
  { 0x04, KG_ARITH, A_SUB },	/* subtract */
  { 0x05, KG_ARITH, A_ADD },	/* add */
  { 0x06, KG_ARITH, A_MUL },	/* multiply */
  { 0x07, KG_ARITH, A_DIV },	/* divide */
  { 0x03, KG_ARITH, A_CHS },	/* change sign*/

  { 0x92, KG_STACK, S_DROP },	/* roll down */
  { 0xa2, KG_STACK, S_SWAP },	/* swap x, y */
  { 0x27, KG_STACK, S_PUSH },	/* push (Enter) */
};

void calc_key( uint8_t k) {

#ifdef DEBUG
  printf("calc_key( 0x%x)\n", k);
#endif  

  if( k == 0x31) {		/* shift (f) key */
    shift = 1;
    return;
  }

  if( !shift && calc_xdigit( k)) {
    shift = 0;			/* digit cancels shift */

    k = calc_xdigit( k);

    int data;

    if( isdigit(k))
      data = k - '0';
    else
      data = toupper(k)-'A'+10;
    
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

#ifdef DEBUGX
	printf("Enter digit %d with X=%" PRIu64 "\n", data, r_x.u64);
#endif      

	uint64_t b = r_x.u64 * radix;
	uint64_t r = b + data;
      
	if( sign) {
	  while( r > MAX_SIGNED(wsize)) {
#ifdef DEBUGX
	    printf("signed compare %" PRIu64 " with %" PRIu64 "\n", r, MAX_SIGNED(wsize));
#endif	    
	    b = delete_high_digit( b, radix);
	    r = b + data;
	  }
	} else {
	  // unsigned
	  while( r > MAX_UNSIGNED(wsize)) {
#ifdef DEBUGX
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

  } // if( calc_xdigit())

  for( int i=0; i<sizeof(keys)/sizeof(keys[0]); i++) {
    if( shift ? (keys[i].key == (k | 0x80)) : (keys[i].key == k)) {

      shift = 0;
      push = 1;

#ifdef STATUS_KEY
      lcd_addr( 40);
      snprintf( msg, sizeof(msg), "key %d %02x %02x", i, k, keys[i].key);
      lcd_puts( msg);
#endif

#ifdef DEBUG
      printf("  match group=%d code=%d\n", keys[i].action_group, keys[i].action_code);
#endif      

      switch( keys[i].action_group) {
      case KG_MODE:
	switch( keys[i].action_code) {

	  // toggle signed mode
	case M_SIG:
	  sign = !sign;
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
	  set_new_word_size( keys[i].action_code);
	  break;
	}
	break;

      case KG_ARITH:

	switch( keys[i].action_code) {
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
	break;

      case KG_STACK:
	switch( keys[i].action_code) {
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
	break;
      }
      calc_update_display();
    }
  }


}
