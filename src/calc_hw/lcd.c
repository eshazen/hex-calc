
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

//
// LCD Pinout
//
// RS   - PB7
// R/W  - GND
// E    - PB6
// D4   - PC0
// D5   - PC1
// D6   - PC2
// D7   - PC3
//

#define LCD_DATA_PORT PORTC
#define LCD_DATA_DDR DDRC
#define LCD_DATA_D0_BIT 0
#define LCD_DATA_MASK 0xf

#define LCD_CTRL_PORT PORTB
#define LCD_CTRL_DDR DDRB
#define LCD_EN_BIT 6
#define LCD_RS_BIT 7

void io_init( void);

void lcd_init( void)
{
  io_init();
  _delay_ms(15);
  send_nibble( 0, 0b0010);
  _delay_ms(5);

  send_nibble(0,0b0010);   //Function set, 4 bit
  send_nibble(0,0b1000);
 
  send_nibble(0,0b0000);   //Display ON, Cursor On, Cursor Blinking
  send_nibble(0,0b1111);

  send_nibble(0,0b0000);   //Clear Display
  send_nibble(0,0b0001);
 
  send_nibble(0,0b0000);  //Entry Mode, Increment cursor position, No display shift
  send_nibble(0,0b0110);
}

void lcd_cls( void)
{
  send_nibble(0,0b0000);   //Clear Display
  send_nibble(0,0b0001);

  lcd_addr( 0);
}
 
void lcd_putc( char c) {
  volatile unsigned char z;	/* why? */
  z = (c >> 4) & 0xf;
  send_nibble( 1, z);
  z = c & 0xf;
  send_nibble( 1, z);
}

// set address.  0=home 
void lcd_addr( uint8_t addr)
{
  volatile uint8_t z;
  z = ((addr >> 4) & 7) | 8;
  send_nibble( 0, z);
  z = addr & 0xf;
  send_nibble( 0, z);
}

void lcd_puts( char *str) {
  volatile char *p = str;	/* why volatile? */
  
  while( *p) {
    lcd_putc( *p);
    ++p;
  }
}

void io_init( void)
{
  LCD_DATA_DDR |= LCD_DATA_MASK;
  LCD_CTRL_DDR |= _BV( LCD_EN_BIT) | _BV( LCD_RS_BIT);
} 


void send_nibble( unsigned char __rs, unsigned char __data)
{
  LCD_DATA_PORT = (__data << LCD_DATA_D0_BIT); /* assert data */
  LCD_CTRL_PORT = (__rs << LCD_RS_BIT) | _BV(LCD_EN_BIT); /* set RS=H & EN=H */
  _delay_ms(1);
  LCD_CTRL_PORT = (__rs << LCD_RS_BIT); /* set RS=H and EN=L */
  _delay_ms(1);
}


