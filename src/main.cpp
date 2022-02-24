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
char pkt_buff[PKT_MAX_SIZE];
int pkt_cnt = 0;

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
            Serial.println("HEADER DETECTED!");
            state = State::COLLECT;
        }
    
    } else if (state == State::COLLECT) {
        // Collect all bytes until newline or MAX_NUMCHARS

        while(n > 0) {
            char c = Serial.read();
            n--;
            
            if (c == '\n' || c == '\r') {
                Serial.println("GOT PACKET!");
                state = State::PARSE;
                // parse and execute commands?
                
                // Reset stuff
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