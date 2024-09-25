#ifndef __LCD_H__
#define __LCD_H__

// width of display
#define LCD_WID 16
// offset to start of 2nd line
#define LCD_LINE2 0x40

void lcd_init( void);
void send_ctrl( unsigned char __data);
void send_data( unsigned char __data);
void lcd_puts( char *str);
void lcd_putc( char c);
void lcd_putch( char c);
void lcd_addr( uint8_t addr);
void lcd_cls( void);

#endif
