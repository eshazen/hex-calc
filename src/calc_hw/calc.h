// #include "calc_top.h"

#include <stdint.h>

#include "int_limits.h"


// display buffer max size
#define DPY_MAX 100

// stack size (match form!)
#define STACK_SIZE 4

#define DEF_RADIX 16
#define DEF_SIZE 16

// mode callback args
#define M_SIG 0
#define M_HEX 1
#define M_DEC 2
#define M_BIN 3
#define M_64 4
#define M_32 5
#define M_16 6
#define M_8 7

// arith callback args
#define A_CLR 0
#define A_SUB 1
#define A_ADD 2
#define A_MUL 3
#define A_DIV 4
#define A_CHS 5

// stack callback args
#define S_DROP 0
#define S_PUSH 1
#define S_SWAP 2

union u_reg {
  uint8_t u8;
  uint16_t u16;
  uint32_t u32;
  uint64_t u64;
};

#ifdef CALC_TOP_MAIN
#define alloc
#else
#define alloc extern
#endif

// global variables
alloc union u_reg r_stack[STACK_SIZE]; /* data stack */
alloc union u_reg r_temp;	       /* temporary reg */
alloc int radix;		       /* current radix */
alloc int wsize;		       /* current word size 8/16/32/64 */
alloc int sign;			       /* signed (1) or unsigned (0) */
alloc int dwidth;		       /* display width 16, 20 or larger */
alloc int drows;		       /* display rows 2, 4 or larger */
alloc int doffset;		       /* horizontal display scroll offset */
alloc int push;			       /* (1) means push on next digit */
alloc int clear;		       /* (1) means clear on next digit */
alloc int shift;		       /* (1) means shift key pressed */

#define r_display r_stack[0]
#define r_x r_stack[0]
#define r_y r_stack[1]
#define r_z r_stack[2]
#define r_t r_stack[STACK_SIZE-1]

// functions

// update stack display
void calc_update_display();
char *format_for_display( union u_reg r);

// sprintf to binary nb bytes
void sp_bin( char *s, int nb, uint64_t v);

// stack ops
void stack_up();
void stack_down();
void stack_down_copy();

// change word size
void set_new_word_size( int size_code);
uint64_t sign_extend( uint64_t v, int siz);
uint64_t mask_bits( uint64_t, int siz);

// formatting
char *insert_every( char *str, int n, char c, int maxc);
void str_rev( char *s);
uint64_t delete_high_digit( uint64_t v, int r);
void reverse_every( char *str, int n);
void display_at( int posn, char label, union u_reg r, uint8_t maxc);
