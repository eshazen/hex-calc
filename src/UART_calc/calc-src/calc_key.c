//
// perform action on key press
//
// keyboard mapping table

// #define DEBUG

#include <ctype.h>
#include "calc.h"

typedef struct {
  char key;
  int action_group;
  int action_code;
} a_key;

// note: digits 0-9 and A-F handled outside this table

#define ctl(c) ((c)-'a'+1)

enum { KG_MODE, KG_ARITH, KG_STACK};

static a_key keys[] = {
  { ctl('s'), KG_MODE, M_SIG },	/* toggle SIGNED display */
  { ctl('h'), KG_MODE, M_HEX },	/* set HEX mode */
  { ctl('d'), KG_MODE, M_DEC },	/* set DEC mode */
  { ctl('t'), KG_MODE, M_BIN },	/* set BIN mode (base Ten) */
  { ctl('o'), KG_MODE, M_64 },	/* set 64-bit word size (Octobyte) */
  { ctl('q'), KG_MODE, M_32 },	/* set 32-bit word size (Quad byte) */
  { ctl('w'), KG_MODE, M_16 },	/* set 16-bit word size (Word) */
  { ctl('b'), KG_MODE, M_8 },	/* set 8-bit word size (Byte) */

  { 'X', KG_ARITH, A_CLR },	/* Clear x */
  { '-', KG_ARITH, A_SUB },	/* subtract */
  { '+', KG_ARITH, A_ADD },	/* add */
  { '*', KG_ARITH, A_MUL },	/* multiply */
  { '/', KG_ARITH, A_DIV },	/* divide */
  { '=', KG_ARITH, A_CHS },	/* change sign*/

  { '\\', KG_STACK, S_DROP },	/* roll down */
  { ctl('m'), KG_STACK, S_PUSH },	/* push (Enter) */
  { ctl('z'), KG_STACK, S_SWAP },	/* swap x, y */
};

void calc_key( char k) {

#ifdef DEBUG
  printf("calc_key( 0x%x)\n", k);
#endif  

  if( isxdigit( k)) {

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

#ifdef DEBUG
	printf("Enter digit %d with X=%" PRIu64 "\n", data, r_x.u64);
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

  for( int i=0; i<sizeof(keys)/sizeof(keys[0]); i++) {
    if( keys[i].key == k) {

#ifdef DEBUG
      printf("  match group=%d code=%d\n", keys[i].action_group, keys[i].action_code);
#endif      

      switch( keys[i].action_group) {
      case KG_MODE:
	switch( keys[i].action_code) {

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
	  set_new_word_size( keys[i].action_code);
	  break;
	default:
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

      default:
      }
      calc_update_display();
    }
  }


}
