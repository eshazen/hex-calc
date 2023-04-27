#include "calc.h"
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

char *format_for_display( union u_reg r_format) {
  
#ifdef DEBUG
  printf("radix: %d  wsize: %d  sign: %d\n", radix, wsize, sign);
#endif

  static char buff[DPY_MAX];
  char *rfmt = buff;

  // ugly nested switch for now
  switch( radix) {

  // binary:  groups of 8 bits with "." separator
  case 2:
    switch( wsize) {
    case 8:
      sp_bin( buff, 1, r_format.u64);
      break;
    case 16:
      sp_bin( buff, 2, r_format.u64);
      break;
    case 32:
      sp_bin( buff, 4, r_format.u64);
      break;
    case 64:
      sp_bin( buff, 8, r_format.u64);
      break;
    default:
      printf("ERROR!  wsize = %d\n", wsize);
    }
    break;

  // decimal: format using snpring, insert commas after
  case 10:
    switch( wsize) {
    case 8:
      if( sign)
	snprintf( buff, sizeof(buff), "%" PRId8, (int8_t)r_format.u8);
      else
	snprintf( buff, sizeof(buff), "%" PRIu8, r_format.u8);
      break;
    case 16:
      if( sign)
	snprintf( buff, sizeof(buff), "%" PRId16, (int16_t)r_format.u16);
      else
	snprintf( buff, sizeof(buff), "%" PRIu16, r_format.u16);
      break;
    case 32:
      if( sign)
	snprintf( buff, sizeof(buff), "%" PRId32, (int32_t)r_format.u32);
      else
	snprintf( buff, sizeof(buff), "%" PRIu32, r_format.u32);
      break;
    case 64:
      if( sign)
	snprintf( buff, sizeof(buff), "%" PRId64, (int64_t)r_format.u64);
      else
	snprintf( buff, sizeof(buff), "%" PRIu64, r_format.u64);
      break;
    default:
      printf("ERROR!  wsize = %d\n", wsize);
    }
    // insert commas
    rfmt = insert_every( buff, 3, ',');
    break;

  // hex: insert "." every 4
  case 16:
    switch( wsize) {
    case 8:
      snprintf( buff, sizeof(buff), "%02" PRIx8, r_format.u8);
      break;
    case 16:
      snprintf( buff, sizeof(buff), "%04" PRIx16, r_format.u16);
      break;
    case 32:
      snprintf( buff, sizeof(buff), "%08" PRIx32, r_format.u32);
      break;
    case 64:
      snprintf( buff, sizeof(buff), "%016" PRIx64, r_format.u64);
      break;
    default:
      printf("ERROR!  wsize = %d\n", wsize);
    }
    rfmt = insert_every( buff, 4, '.');
    break;


  default:
    break;
  }

  
  return rfmt;
}


// update display from r_display
// use radix, wsize, sign
void calc_update_display() {
#ifdef USING_XFORMS
  fl_set_object_label( fd_calc_top->reg_X, format_for_display( r_x));
  fl_set_object_label( fd_calc_top->reg_Y, format_for_display( r_y));
  fl_set_object_label( fd_calc_top->reg_Z, format_for_display( r_z));
  fl_set_object_label( fd_calc_top->reg_T, format_for_display( r_t));
#endif

#ifdef USE_TTY
  printf( "%s\n", "--------------------");
  printf( "%s\n", format_for_display( r_t));
  printf( "%s\n", format_for_display( r_z));
  printf( "%s\n", format_for_display( r_y));
  printf( "%s\n", format_for_display( r_x));
#endif  
}


// binary print byte
char *sp_byt( char *s, uint8_t v) {
  for( int i=0, b=0x80; 
       i++, b>>=1; 
       i<8)
    *s++ = ((v & b) ? '1' : '0');
  return s;
}

void sp_bin( char *s, int nb, uint64_t v) {
  char *p = s;
  uint8_t b;

  // loop over nb bytes
  for( int i=0; i<nb; i++) {
    // extract byte to print
    b = (v >> 8*(nb-i-1));
    p = sp_byt( p, b);
    if( i != nb-1)
      *p++ = '.';
  }
  *p++ = '\0';
}


// push stack up, duplicating X
void stack_up() {
  for( int i=STACK_SIZE-1; i>0; i--)
    r_stack[i] = r_stack[i-1];
}

// roll stack down, copying X to T
void stack_down() {
  r_temp = r_display; /* save X */
  for( int i=0; i<STACK_SIZE-1; i++)
    r_stack[i] = r_stack[i+1];
  r_t = r_temp;
}

// roll stack down, duplicating T
void stack_down_copy() {
  stack_down();
  r_t = r_z;
}

// change word size
// if increasing and in signed mode, sign-extend
// keep track of old size
void set_new_word_size( int size_code)
{
  static int old_size = DEF_SIZE;
  int new_size;

  switch( size_code) {
  case M_64:
    new_size = 64;
    break;
  case M_32:
    new_size = 32;
    break;
  case M_16:
    new_size = 16;
    break;
  case M_8:
    new_size = 8;
    break;
  default:
    printf("ERROR!  size code: %d should be between %d and %d (inclusive)\n",
	   size_code, M_64, M_8);
  }

#ifdef DEBUG  
  printf("Set word size (old=%d new=%d)\n", old_size, new_size);
#endif  
  wsize = new_size;

  // sign-extend all stack regs to 64 bits if word size larger
  if( (new_size > old_size) && sign) {
    for( int i=0; i<STACK_SIZE; i++)
      r_stack[i].u64 = sign_extend( r_stack[i].u64, old_size);
  }

  // mask high bits if word size smaller
  if( new_size < old_size) {
    for( int i=0; i<STACK_SIZE; i++)
      r_stack[i].u64 = mask_bits( r_stack[i].u64, new_size);
  }

  old_size = wsize;
}

//
// sign-extend from value v interpreted as int8/16/32/64 to 64 bits
//
uint64_t sign_extend( uint64_t v, int siz) {

#ifdef DEBUG
  printf("Sign extend 0x%" PRIx64 " from %d bits\n", v, siz);
#endif
  int64_t r = v;
  
  if( siz < 64) {
    for( int i=siz; i<64; i++) {
#ifdef DEBUG
      printf(" bit %d test: %d\n", i, (v & (1LL << (siz-1))) != 0);
#endif
      if( v & (1LL << (siz-1)))
	r |= 1LL << i;
    }
  }

  return r;
}



//
// zero bits above siz
//
uint64_t mask_bits( uint64_t v, int siz) {

  uint64_t r = v;
  
  switch( siz) {
  case 32:
    r &= 0xffffffff;
    break;
  case 16:
    r &= 0xffff;
    break;
  case 8:
    r &= 0xff;
    break;
  default:
    break;
  }

  return r;
}


// start at end of string, insert c every n characters
// return pointer to static (modified) copy
// only insert after digits
char *insert_every( char *str, int n, char c) {

#ifdef DEBUG
  printf("insert_every( \"%s\", %d, '%c')\n",
	 str, n, c);
#endif
  
  static char buff[DPY_MAX];
  char *dp = buff;		/* destination pointer */
  char *sp = &str[strlen(str)-1]; /* source pointer, last char of input string */
  char lastc;

  if( strlen(str) < n)		/* protect against short string */
    return str;

  for( size_t i=0; i<strlen(str); i++) {
    if( i > 0 && !(i % n) && isxdigit(*sp)) {
#ifdef DEBUG
      printf("Inserting %c before %c\n", c, *sp);
#endif
      *dp++ = c;
    }
    lastc = *dp++ = *sp--;
  }
  *dp++ = '\0';
#ifdef DEBUG
  printf("insert_every first result = \"%s\"\n", buff);
#endif
  str_rev( buff);
  return buff;
}

// swap two chars in place
void swap_char( char *cx, char *cy) {
  *cx = *cx ^ *cy;
  *cy = *cx ^ *cy;
  *cx = *cx ^ *cy;
}

// reverse a string in place
void str_rev( char *s) {
  int n = strlen(s);

#ifdef DEBUG
  printf("str_rev( \"%s\")\n", s);
#endif
  if( !n) return;			/* protect against empty strings */
  if( n < 4)
    swap_char( &s[0], &s[n-1]);
  else {
    for( int i=0; i<n/2; i++)
      swap_char(&s[i], &s[n-i-1]);
  }
#ifdef DEBUG
  printf("str_rev( \"%s\")\n", s);
#endif
}
  


//
// subtract the most-significant non-zero digit from v with radix
//
uint64_t delete_high_digit( uint64_t v, int radix)
{
  int nd = 0;
  uint64_t t = v;
  uint64_t s = 1;

#ifdef DEBUG
  printf("delete_high_digit( %" PRIu64 " (0x%" PRIx64 "), %d\n", v, v, radix);
#endif  

  if( v < (uint64_t)radix)
    return 0;

  // find highest non-zero digit by successive division
  while( t > (uint64_t)radix && nd < 32) {
    nd++;
    t /= radix;
    s *= radix;
  }
  v -= (s*t);

#ifdef DEBUG
  printf("  result: %" PRIu64 "( 0x%" PRIx64 ") nd=%d\n", v, v, nd);
#endif  

  return v;
}

