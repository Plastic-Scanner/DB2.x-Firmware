#include "command.h"
#include <errno.h>
#include <Arduino.h>

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

    const char* delimiters = " ";
    char *token = strtok(rx_buf, delimiters);
    while (token != NULL) {
        argv[argc++] = token;
        token = strtok(NULL, delimiters);
    }

    if (argc < 1) return;
    if      (strcmp(argv[0], "SCAN") == 0) Serial.println("SCANNING");
    else if (strcmp(argv[0], "ADC") == 0) Serial.println("READING ADC");
    else if (strcmp(argv[0], "LED") == 0) {
        if (argc == 3) {
            int num;
            bool state;

            num = (int)strtol(argv[1], NULL, 10);
            // if (errno > 0) fail();
            if      (strcmp(argv[2], "ON") == 0) state = true;
            else if (strcmp(argv[2], "OFF") == 0) state = false;
            // else fail(BAD_ARGS);

            // Dummy function call
            Serial.println("LED ");
            Serial.println(num);
            Serial.println("ON") ? state == true : Serial.println("OFF");
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

void Command::begin()
{
    reset();
}
