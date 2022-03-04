#include "command.h"
#include <CircularBuffer.h>
#include <Arduino.h>

enum State {
    IDLE,           // Wait for HEADER ("DB")
    COLLECT         // Collect all chars until ENDCHAR (\n or \r) or MAX_NUMCHARS
};
State state;

const int CMD_MAXCHARS = 12;        // COMMAND size limit (excl. header)
char cmd_buff[CMD_MAXCHARS];        // COMMAND buffer
int cmd_cnt;
CircularBuffer<char, 2> hdr_buff;   // HEADER buffer/sliding-window

// Helper debugging function
static void printbuf(char *ptr, int n) 
{
    Serial.print("NCHARS = ");
    Serial.print(n);
    Serial.println();
    Serial.print("ASCII: ");
    for (int i=0; i<n; i++) {
        Serial.print(ptr[i]);
    }
    Serial.println();
    Serial.print("DEC: ");
    for (int i=0; i<n; i++) {
        Serial.print(ptr[i], DEC);
        Serial.print(" ");
    }
}

static void reset()
{
    memset(cmd_buff, 0, sizeof(cmd_buff));
    cmd_cnt = 0;
}

void Command::begin(
    void (*scan)(), 
    void (*adc)(),
    void (*ledon)(int),
    void (*ledoff)(int), 
    void (*unknown)() ) {
    
    this->scan_fptr = scan;
    this->adc_fptr = adc;
    this->ledon_fptr = ledon;
    this->ledoff_fptr = ledoff;
    this->unknown_fptr = unknown;
    
    state = State::IDLE;
    reset();
}

void Command::handle()
{
    if (state == State::IDLE) {
        int n = Serial.available();
        while (n > 0) {
            hdr_buff.push(Serial.read());                   // Shift sliding window one char left
            n--;
            if ((hdr_buff.first() == 'D') && 
                (hdr_buff.last() == 'B')) {                 // Change state if header detected
                hdr_buff.clear();
                state = State::COLLECT;
            }
        }

    } else if (state == State::COLLECT) {
        int n = Serial.available();
        while (n > 0) {
            char c = Serial.read();
            cmd_buff[cmd_cnt] = c;              // Read char into command buffer
            cmd_cnt++;
            n--;
            if (c == '\n' || c == '\r') {
                cmd_buff[cmd_cnt] = 0;          // Replace end of command delimiter w/ null-terminator
                parse_command(cmd_buff);
                reset();
                state = State::IDLE;
            } else if (cmd_cnt == CMD_MAXCHARS) {
                Serial.println("ERROR: COMMAND TOO LONG");
                reset();
                state = State::IDLE;
            }
        }
    }
}

void Command::parse_command(char *ptr)
{
    const char *DELIMITERS = " \n\r";
    char *token = strtok(ptr, DELIMITERS);

    if      (strcmp(token, "SCAN") == 0) scan_fptr();
    else if (strcmp(token, "ADC") == 0)  adc_fptr();
    else if (strcmp(token, "LEDON") == 0) {
        token = strtok(NULL, DELIMITERS);               // Read parameter #1
        if (token != NULL) ledon_fptr(strtol(token, NULL, 10));
        else Serial.println("BAD ARGUMENTS");
    
    } else if (strcmp(token, "LEDOFF") == 0) {
        token = strtok(NULL, DELIMITERS);               // Read parameter #1
        if (token != NULL) ledoff_fptr(strtol(token, NULL, 10));
        else Serial.println("BAD ARGUMENTS");

    } else unknown_fptr();
}
