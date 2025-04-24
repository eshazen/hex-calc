//
// keyboard scanning
//
// kb_init() once to setup ports
// poll_kb() periodically to scan (8ms works well)
//   recognized hits are pushed into circular buffer
// get_kb() returns 0 or next hit code from buffer
//
// hit code:  row# 1-7 in low 4 bits
//            col# 0-3 in upper 4 bits
//

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_DEBUG

// #define DEBOUNCE_DELAY 10
#define DEBOUNCE_DELAY 5

static uint8_t bouncy;

#include "led.h"
#include "kb.h"

uint8_t kb_val[ NUM_KB_COL];	/* last scanned values */

//
// initialize KB ports
//
void kb_init() {
  // keyboard columns as output
  DDRB |= _BV(KB_COL0);
  DDRC |= _BV(KB_COL1) | _BV(KB_COL2);
  DDRD |= _BV(KB_COL3);
  
  // pull-ups on KB rows
  KB_ROW_PORT |= KB_ROW_MASK;
}

//
// select KB column 0-3
//
void set_kb_col( uint8_t c) {
  // drive all columns high
  KB_COL0_PORT |= _BV(KB_COL0);
  KB_COL1_PORT |= _BV(KB_COL1);
  KB_COL2_PORT |= _BV(KB_COL2);
  KB_COL3_PORT |= _BV(KB_COL3);

  // drive selected column low
  switch( c) {
  case 0:
    KB_COL0_PORT &= ~_BV(KB_COL0);
    break;

  case 1:
    KB_COL1_PORT &= ~_BV(KB_COL1);
    break;
    
  case 2:
    KB_COL2_PORT &= ~_BV(KB_COL2);
    break;
    
  case 3:
    KB_COL3_PORT &= ~_BV(KB_COL3);
    break;
  }
}

// keyboard type-ahead buffer size, must be power of 2
#define KB_BUFFSIZ 4

static uint8_t kb_buff[KB_BUFFSIZ];
volatile uint8_t kb_head, kb_tail;

// advance pointer with wrap
#define kb_next(k) ((k+1)&(KB_BUFFSIZ-1))
// check for full
#define kb_full() (kb_next(kb_head)==kb_tail)
// check for empty
#define kb_empty() (kb_head==kb_tail)
// push to buffer
#define _push_kb(k) (kb_buff[kb_head]=k,kb_head=kb_next(kb_head))

// return next code or 0
uint8_t get_kb() {
  uint8_t k;
  if( kb_empty())
    return 0;
  cli();
  k = kb_buff[kb_tail];
  kb_tail = kb_next(kb_tail);
  sei();
  return k;
}


void poll_kb() {
  uint8_t k = scan_kb();
  if( k && !kb_full()) {
    _push_kb( k);
  }
}

// scan keyboard for hits
// zero if no hits, else an integer code
uint8_t scan_kb() {

  if( bouncy > 0) {
    --bouncy;
    return 0;
  }

  // local variables static to simplify
  static uint8_t kb_v;
  static uint8_t kb_d;
  static uint8_t kb_code;
  static uint8_t kb_rc;

  kb_rc = 0;

  for( uint8_t c=0; c<NUM_KB_COL; c++) { /* loop over (4) KB columns */

    set_kb_col( c);		/* assert one column */
    kb_v = read_kb();		/* read 7-bit row value */
    kb_d = kb_val[c] ^ kb_v;	/* any changes? */
    if( kb_d) {			/* yes */
      kb_code = 1;
      for( uint8_t b=1; b<0x80; b<<=1) { /* see which bit changed */
	if( (kb_d & b) && (kb_v & b)) {	 /* only press, no release */
	  kb_rc = (c << 4) | kb_code;
	}
	++kb_code;
      }
    }
    kb_val[c] = kb_v;		/* remember last value for column */
  }

  bouncy = DEBOUNCE_DELAY;
  return kb_rc;
}
