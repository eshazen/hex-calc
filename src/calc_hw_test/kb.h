#ifndef __KB_H__
#define __KB_H__



#include <avr/io.h>

// KB column bits
#define KB_COL0 2
#define KB_COL1 4
#define KB_COL2 5
#define KB_COL3 7

// KB column ports
#define KB_COL0_PORT PORTB
#define KB_COL1_PORT PORTC
#define KB_COL2_PORT PORTC
#define KB_COL3_PORT PORTD

// KB row ports and mask
#define KB_ROW_PIN PIND
#define KB_ROW_PORT PORTD
#define KB_ROW_MASK 0x7f

#define NUM_KB_COL 4

#define read_kb() (~(KB_ROW_PIN & KB_ROW_MASK))

void kb_init();
void set_kb_col( uint8_t c);
uint8_t scan_kb();
void push_kb( uint8_t k);
void poll_kb();
uint8_t get_kb();

#endif
