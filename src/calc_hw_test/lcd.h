#ifndef __LCD_H__
#define __LCD_H__

void lcd_init( void);
void io_init( void);
void send_nibble( unsigned char __rs, unsigned char __data);
void lcd_puts( char *str);
void lcd_putc( char c);
void lcd_addr( uint8_t addr);
void lcd_cls( void);

#endif
