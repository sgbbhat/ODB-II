#ifndef LCD_H_
#define LCD_H_

#include "common.h"
#include "serial.h"

/*
D_I PORTD1
R_W PORTD0
E   PORTD4 (4)
*/
#define LCDOUT  PORTB

// output-RS-RW-E
#define PULLUP_OUT_REGS() {\
    DDRB = 0xf0;\
    SET(DDRD, DDD1);\
    SET(DDRD, DDD0);\
    SET(DDRD, DDD4);\
    SET(DDRC, DDC7);\
}

#define MAX_STRLEN 40

/** Initialize the LCD (4-bit mode) */
void lcd_init();

/** print a single character on LCD 
 * @param c     a charcter to print
 * */
void lcd_print_char(char c);

/** print a string to LCD 
 * @param str   a string to print 
 * */
void lcd_print_str(char *str);

#endif

