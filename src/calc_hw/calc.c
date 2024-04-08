#include "calc.h"
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

#include "avr_helper.h"
#include "lcd.h"

// #define STATUS_LINE
// #define REVERSE_EVERY
#define INSERT_EVERY

extern char msg[LCD_WID+2];
static char dpy_buff[DPY_MAX];

//
// format register for display, taking into account
//   wsize( 8/16/32/64), radix (2/10/16) and sign (0/1)
//
char *format_for_display( union u_reg r_format) {
  
  char *rfmt = dpy_buff;

  // ugly nested switch for now
  switch( radix) {

  // binary:  groups of 8 bits with "." separator
  case 2:
    switch( wsize) {
    case 8:
      sp_bin( dpy_buff, 1, r_format.u64);
      break;
    case 16:
      sp_bin( dpy_buff, 2, r_format.u64);
      break;
    case 32:
      sp_bin( dpy_buff, 4, r_format.u64);
      break;
    case 64:
      sp_bin( dpy_buff, 8, r_format.u64);
      break;
    }

#ifdef REVERSE_EVERY
    if( wsize > 8) reverse_every( dpy_buff, 8);
#endif
    
    break;

  // decimal: format using snprintf, insert commas after
  case 10:
    switch( wsize) {
    case 8:
      if( sign)
	snprintf( dpy_buff, sizeof(dpy_buff), "%" PRId8, (int8_t)r_format.u8);
      else
	snprintf( dpy_buff, sizeof(dpy_buff), "%" PRIu8, r_format.u8);
      break;
    case 16:
      if( sign)
	snprintf( dpy_buff, sizeof(dpy_buff), "%" PRId16, (int16_t)r_format.u16);
      else
	snprintf( dpy_buff, sizeof(dpy_buff), "%" PRIu16, r_format.u16);
      break;
    case 32:
      if( sign)
	snprintf( dpy_buff, sizeof(dpy_buff), "%" PRId32, (int32_t)r_format.u32);
      else
	snprintf( dpy_buff, sizeof(dpy_buff), "%" PRIu32, r_format.u32);
      break;
    case 64:
      if( sign)
#ifdef AVR
	// NOTE: this needs to be signed
	snprintf( dpy_buff, sizeof(dpy_buff), "%s", uint64_to_str( (int64_t)r_format.u64));
#else	
	snprintf( dpy_buff, sizeof(dpy_buff), "%" PRId64, (int64_t)r_format.u64);
#endif
      else
#ifdef AVR
	snprintf( dpy_buff, sizeof(dpy_buff), "%s", uint64_to_str( (int64_t)r_format.u64));
#else	
	snprintf( dpy_buff, sizeof(dpy_buff), "%" PRIu64, r_format.u64);
#endif
      break;
    }
    // insert commas
    // <ESH> why?
#ifdef INSERT_EVERY
    rfmt = insert_every( dpy_buff, 3, ',', sizeof(dpy_buff));
#endif    
    break;

  // hex: insert "." every 4
  case 16:
    switch( wsize) {
    case 8:
      snprintf( dpy_buff, sizeof(dpy_buff), "%02" PRIx8, r_format.u8);
      break;
    case 16:
      snprintf( dpy_buff, sizeof(dpy_buff), "%04" PRIx16, r_format.u16);
      break;
    case 32:
      snprintf( dpy_buff, sizeof(dpy_buff), "%08" PRIx32, r_format.u32);
      break;
    case 64:
#ifdef AVR
      snprintf( dpy_buff, sizeof(dpy_buff), "%08" PRIx32 "%08" PRIx32,
		(uint32_t)(r_format.u64 >> 32LL), (uint32_t)(r_format.u64 & 0xffffffffLL));
#else      
      snprintf( dpy_buff, sizeof(dpy_buff), "%016" PRIx64, r_format.u64);
#endif
      break;
    default:
      printf("ERROR!  wsize = %d\n", wsize);
    }
#ifdef REVERSE_EVERY
    if( wsize < 64)      reverse_every( dpy_buff, 4);
#endif
    break;

  default:
    break;
  }

  
  return rfmt;
}

//
// display at LCD position posn, optional single-character label, register reg
// max width is maxc.  If > width, wrap to next line
//
void display_at( int posn, char label, union u_reg reg, uint8_t maxc) {
  char *fmt = format_for_display( reg);
  lcd_addr( posn);
  if( label) {
    snprintf( msg, maxc+1, "%c:%s", label, fmt);
  } else {
    if( maxc <= LCD_WID)	/* width <= display width */
      snprintf( msg, maxc+1, "%s", fmt);
    else {			/* width exceeds display width, just assume it's 32 */
      snprintf( msg, LCD_WID+1, "%s", fmt);
      if( strlen( fmt) > LCD_WID) {
	lcd_puts( msg);
	lcd_addr( LCD_LINE2);
	snprintf( msg, LCD_WID+1, "%s", fmt+LCD_WID);
      }
    }
  }
  lcd_puts( msg);
}

// update display from r_display
// use radix, wsize, sign
void calc_update_display() {
  lcd_cls();

  // various formats based on size / base
  switch( radix) {
  case 16:			/* ------ HEX display ------ */

    switch( wsize) {
    case 8:
    case 16:
      // display X/Y/Z/T
      display_at( 0, 'T', r_t, 8);
      display_at( 8, 'Z', r_z, 8);
      display_at( LCD_LINE2, 'Y', r_y, 8);
      display_at( LCD_LINE2+8, 'X', r_x, 8);
      break;
      
    case 32:
      display_at( 0, 'Y', r_y, LCD_WID);
      display_at( LCD_LINE2, 'X', r_x, LCD_WID);
      break;

    case 64:
      display_at( 0, '\0', r_x, LCD_WID);
      display_at( LCD_LINE2, '\0', r_y, LCD_WID);
      break;
    }
    break;
    
  case 10:			/* ------ DEC display ------ */
    //    snprintf( msg, LCD_WID, "Dec: %s", format_for_display( r_x));
    //    lcd_puts( msg);
    display_at( 0, 'Y', r_y, LCD_WID);
    display_at( LCD_LINE2, 'X', r_x, LCD_WID);
    break;
    
  case 2:			/* ------ BIN display ------ */
    switch( wsize) {
    case 8:
      display_at( 0, 'Y', r_y, LCD_WID);
      display_at( LCD_LINE2, 'X', r_x, LCD_WID);
      break;

    case 16:
      display_at( 0, '\0', r_y, LCD_WID);
      display_at( LCD_LINE2, '\0', r_x, LCD_WID);
      break;

    case 32:
      display_at( 0, '\0', r_x, LCD_WID*2);      
      break;

    case 64:
      lcd_puts("too big");
      break;

    }
  }
}


// binary print byte
char *sp_byt( char *s, uint8_t v) {
  for( int i=0, b=0x80;
       i<8;
       i++, b>>=1)
    *s++ = ((v & b) ? '1' : '0');
  return s;
}

// print binary value of nb bytes with dot separator
void sp_bin( char *s, int nb, uint64_t v) {
  char *p = s;
  uint8_t b;

  // loop over nb bytes
  for( int i=0; i<nb; i++) {
    // extract byte to print
    b = (v >> 8*(nb-i-1LL));
    p = sp_byt( p, b);
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
  }

  wsize = new_size;

  // sign-extend all stack regs to 64 bits if word size larger
  if( (new_size > old_size) && sign) {
    for( int i=0; i<STACK_SIZE; i++)
      r_stack[i].u64 = sign_extend( r_stack[i].u64, old_size);
    // mask high bits if word size smaller
  } else if( new_size < old_size) {
    for( int i=0; i<STACK_SIZE; i++)
      r_stack[i].u64 = mask_bits( r_stack[i].u64, new_size);
  }
  // ... no action if the same
  old_size = wsize;
}

//
// sign-extend from value v interpreted as int8/16/32/64 to 64 bits
//
uint64_t sign_extend( uint64_t v, int siz) {

  int64_t r = v;
  
  if( siz < 64) {
    for( int i=siz; i<64; i++) {
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
  }

  return r;
}


#ifdef REVERSE_EVERY
// invert (reverse) characters every n characters
// char codes 1-8 are 01ABCDEF
void reverse_every( char *str, int n) {
  for( size_t i=0; i<strlen(str); i++) {
    unsigned char c = toupper(*str);
    if( i%n == 0) {
      if( c == '0' || c == '1')	/* convert '0' to 0x1, '1' to 0x2 */
	c = c - '0' + 1;
      else if( c >= 'A' && c <= 'F') /* convert 'A' to 3 etc */
	c = c - 'A' + 3;
    }
    *str++ = c;
  }
}
#endif

#ifdef INSERT_EVERY
// start at end of string, insert c every n characters
// modify in place but don't exceed buffer size maxc
char *insert_every( char *str, int n, char c, int maxc) {
  int rl = strlen( str);	/* keep track of result length */
  int cp;
  if( rl > 3) {
    cp = rl-3;
    while( cp > 0 && rl < (maxc-1)) {
      memmove( str+cp+1, str+cp, rl-cp+1);
      str[cp] = c;
      cp -= 3;
      rl++;
    }
  }
  return str;
}
#endif  


//
// subtract the most-significant non-zero digit from v with radix
//
uint64_t delete_high_digit( uint64_t v, int radix)
{
  int nd = 0;
  uint64_t t = v;
  uint64_t s = 1;

  if( v < (uint64_t)radix)
    return 0;

  // find highest non-zero digit by successive division
  while( t > (uint64_t)radix && nd < 32) {
    nd++;
    t /= radix;
    s *= radix;
  }
  v -= (s*t);
  return v;
}

