#include "command.h"
#include "assert.h"
#include "errno.h"
#include <Arduino.h>

/*
    Exapmple of commands (ignore the $ sign):
    $ SCAN
    $ ADC
    $ LED 1 ON
*/

static const int RX_BUF_SIZE = 20;
static const int MAX_ARGS = 3;

static char rx_buf[RX_BUF_SIZE];
static int rx_cnt;

static void reset()
{
    rx_cnt = 0;
    memset(rx_buf, 0, RX_BUF_SIZE);
}

void Command::parse_command()
{
    int argc = 0;
    char *argv[MAX_ARGS] = {0};
    bool args_ok = true;

    const char* delimiters = " ";
    char *token = strtok(rx_buf, delimiters);
    while (token != NULL) {
        argv[argc++] = token;
        token = strtok(NULL, delimiters);
    }

    if      (0 == strcmp(argv[0], "SCAN")) { 
        if (scan != nullptr) scan();

    } else if (0 == strcmp(argv[0], "ADC")) {
        if (adc != nullptr) adc();

    } else if (0 == strcmp(argv[0], "LED")) {
        int num;
        bool state;
        
        if (argc == 3) {
            errno = 0;
            num = (int)strtol(argv[1], NULL, 10);
            if (errno != 0) args_ok = false;            // TODO: this doesn't really work atm

            if      (strcmp(argv[2], "ON") == 0) state = 1;
            else if (strcmp(argv[2], "OFF") == 0) state = 0;
            else args_ok = false;
        } else {
            args_ok = false;
        }
    
        if (args_ok) {
            if (led != nullptr) led(num, state);
        } else {
            Serial.println("Bad arguments");
        }
    } else {
        if (unknown != nullptr){
            unknown();
        }
    }
}


void Command::handle()
{
    int n = Serial.available();
    while (n > 0) {
        char c = Serial.read();
        if (c == '\b') {                    // backspace
            rx_buf[--rx_cnt] = '\0';

        } else if (rx_cnt == RX_BUF_SIZE) { // buffer overflow
            reset();
        
        } else if (c == '\n' || c == '\r') {
            parse_command();
            reset();
        
        } else {
            rx_buf[rx_cnt++] = c;           // add to buffer
        }
        n--;
    }
}

void Command::begin(
    void (*scan)(), 
    void (*adc)(),
    void (*led)(int, bool),
    void (*unknown)())
{
    this->scan = scan;
    this->adc = adc;
    this->led = led;
    this->unknown = unknown;
    reset();
}
