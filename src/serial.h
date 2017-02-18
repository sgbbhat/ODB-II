#ifndef SERIAL_H_
#define SERIAL_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"

#define BAUD_RATE 38400

void setup_serial();
void print_char(uint8_t c);
void print_str(const char *s);
void print_int(int n);
void print_err_msg(const char *s);
bool get_cmd(char*, uint32_t*);
void print_menu();

#endif
