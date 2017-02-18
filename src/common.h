#ifndef COMMON_H_
#define COMMON_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <util/delay.h>
#include <assert.h>

#define F_CPU 16000000

#define DEBUG true

// Port-bit manipulators
#define TST(port, bit) ((port) & (1 << (bit)))
#define SET(port, bit) ((port) |= (1 << (bit)))
#define CLR(port, bit) ((port) &= ~(1 << (bit)))
#define TOG(port, bit) ((port) ^= (1 << (bit)))

#define TURN_LED(port, n, on) ({\
        if (on > 0) SET(port, n);\
        else if (on == 0) CLR(port, n);\
        else TOG(port, n);\
        })
#define turn_led_y(on) TURN_LED(PORTC, PORTC7, on)
#define turn_led_r(on) TURN_LED(PORTB, PORTB0, on)
#define turn_led_g(on) TURN_LED(PORTD, PORTD5, on)

#define SETUP_LEDS() ({\
        SET(DDRB, DDB6);\
        SET(DDRD, DDD4);\
        SET(DDRC, DDD6);\
        SET(DDRB, DDB0);\
        SET(DDRD, DDD5);\
        SET(DDRD, DDD6);\
        SET(DDRC, DDC7);\
        })
/*
        //SET(DDRB, DDB5);\

#define SETUP_BTNS() ({\
        CLR(DDRB, DDB0);\
        CLR(DDRB, DDB3);\
        SET(PORTB, PORTB0);\
        SET(PORTB, PORTB3);\
        })
        //SET(PCICR, PCIE0);\
        //SET(PCMSK0, PCINT0);\
        //SET(PCMSK0, PCINT3);\

#define turn_led_yy(on) TURN_LED(PORTD, PORTD4, on)
#define turn_led_rr(on) TURN_LED(PORTD, PORTD6, on)
*/
#endif

