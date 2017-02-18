#include "serial.h"
#include "common.h"

// The code is mostly written by 

//Length of buffer used to store user configuration option
#define RCV_BUF_LEN 50
#define OUT_BUF_LEN 200

//Serial communication: data receipt buffer
static volatile char rcv_buf[RCV_BUF_LEN];
static volatile char out_buf[OUT_BUF_LEN];
volatile uint8_t rcv_buf_ptr = 0;
volatile bool cmd_ready = false;

const char *menu = "\n[Menu]\n\
 (p): print data collected for experiment\n\
 (e #): Set-up this experiment number\n\
 (r #): Set the period of the GREEN LED Task to # of ms\n\
 (z): Reset all variables to set-up for a new experiment\n\
 (g): Go signal for start experiment\n";

void setup_serial(void) {
    UBRR1 = ((F_CPU/(16*BAUD_RATE)) - 1);
    SET(UCSR1C, UCSZ11);
    SET(UCSR1C, UCSZ10);
    SET(UCSR1B, TXEN1);		// enable transmit
    SET(UCSR1B, RXEN1);		// enable receive
    SET(UCSR1B, RXCIE1);	// enable interrupt on data receipt
}

void print_char(uint8_t c) {
    // wait while data register is NOT empty
    while((UCSR1A & (1<<UDRE1)) == 0);	
    UDR1 = c;
}

void print_str(const char *s) {
    while(*s != 0x00) {
        print_char(*s);
        s++;
    }
}

void print_int(int n) {
    char str[10];
    snprintf(str, 10, "%d", n);
    print_str(str);
}

void print_menu() {
    print_str(menu);
}

/** print an error message */
void print_err_msg(const char *msg) {
    sprintf(out_buf, "%s, while parsing %s\n", msg, rcv_buf);
    print_str(out_buf);
}

/** retrieve the command entered by user */
bool get_cmd(char *cmd, uint32_t *param) {
    bool retval = false;
    memset((void*)out_buf, 0, OUT_BUF_LEN);
    if (strlen(rcv_buf) == 1) {
        // single character option
        sscanf(rcv_buf, "%c", cmd);
        *param = 0;
        retval = true;
    } else if (strlen(rcv_buf) > 1) {
        // numeric option
        uint32_t flag = sscanf(rcv_buf, "%c %u", cmd, param);
        if ((flag == EOF) || (flag != 2)) {
            print_err_msg("invalid command");
            retval = false;
        } 
        retval = true;
    }

    memset((void*)rcv_buf, 0, RCV_BUF_LEN);
    rcv_buf_ptr = 0;
    return retval;
}

//ISR that is called whenever there is data to receive
ISR (USART1_RX_vect) {
    uint8_t ch = UDR1;
    turn_led_g(-1);
    if (ch == 13 || (rcv_buf_ptr >= RCV_BUF_LEN)) {
        // enter pressed
        cmd_ready = true;
    } else if (ch == 8) {
        //User deletes a character
        if (rcv_buf_ptr >= 1)
            --rcv_buf_ptr;
        rcv_buf[rcv_buf_ptr] = 0;
    } else if ( (ch == 32) || ((ch >= 48) && (ch <= 57)) || 
            ((ch >= 65) && (ch <= 90)) || ((ch >= 97) && (ch <= 122)) ) {
        //Only store alphanumeric symbols and space
        rcv_buf[rcv_buf_ptr] = ch;
        ++rcv_buf_ptr;
    }
}

