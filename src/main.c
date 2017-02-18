#include "common.h"
#include "lcd.h"
#include "serial.h"
#include <stdio.h>

int main() {
    SETUP_LEDS();
    setup_serial();
    lcd_init();
   
    lcd_print_str("hello LCD!"); 
    lcd_print_str("May I scare you a little bit?"); 
    _delay_ms(500);
    lcd_print_str("Initializing..\n(Segmentation Fault)"); 
    while (true) {
        SET(PORTC, PORTC7);
        _delay_ms(10);
        CLR(PORTC, PORTC7);
        _delay_ms(2);
    }

    return 0;
}

