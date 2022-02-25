/*
    Arduino firmware for the DB2.x
    Run with: 
        pio run --target upload && pio device monitor
*/
#include "packet.h"
#include "assert.h"
#include <Arduino.h>

Packet pkthandler;

void setup()
{
    Serial.begin(9600);
    Serial.println("Initialized");
}


#include <CircularBuffer.h>

const int header_chars = 2;
CircularBuffer<char, 2> buff;

enum State {IDLE, COLLECT, PARSE};
State state = IDLE;

const int PKT_MAX_SIZE = 12;
char pkt_buff[PKT_MAX_SIZE] = {0};
int pkt_cnt = 0;


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

void parse_command(char *ptr, int nchars)
{
    const char *DELIMITER = " ";
    char *token = strtok(ptr, DELIMITER);
    if (token == NULL) {
        Serial.println("BAD COMMAND!");
        return;
    }


    if      (strncmp(token, "SCAN", nchars) == 0) Serial.println("SCANNING!");
    else if (strncmp(token, "ADC", nchars) == 0)  Serial.println("ADC MEASUREMENT");
    else Serial.println("UNKNOWN COMMAND");
}

void loop()
{

    int n = Serial.available(); // is it ugly to have this outside of state functions? yes...
    if (n == 0) return;

    if (state == State::IDLE) {
        if (buff.size() == header_chars) {
            buff.push(Serial.read());           // Shift left, read a single character
        } else {
            while ((buff.size() < header_chars) && (n > 0)) {   // Buff not full, fill it
                buff.push((char)Serial.read());
                n--;
            }
        }

        // Change state if header detected
        if ((buff.first() == 'D') && 
             (buff.last() == 'B')) {
            buff.clear();
            state = State::COLLECT;
        }
    
    } else if (state == State::COLLECT) {
        // Collect all bytes until newline or MAX_NUMCHARS

        while(n > 0) {
            char c = Serial.read();
            n--;
            
            if (c == '\n' || c == '\r') {
                state = State::PARSE;
                // Add a null-terminator at the end
                pkt_cnt++;
                pkt_buff[pkt_cnt] = 0;
                parse_command(pkt_buff, pkt_cnt);
                memset(pkt_buff, 0, sizeof(pkt_buff));
                pkt_cnt = 0;
                state = State::IDLE;
            } else if (pkt_cnt == PKT_MAX_SIZE) {
                Serial.println("ERROR: COMMAND PACKET TOO LONG");
                pkt_cnt = 0;
                state = State::IDLE;
            } else {
                pkt_buff[pkt_cnt] = c;
                pkt_cnt++;
            }
        }
    }
}