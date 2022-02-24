/*
    Arduino firmware for the DB2.x
    Run with: 
        pio run --target upload && pio device monitor
*/
#include "assert.h"
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
    Serial.println("Initialized");
}


#include <CircularBuffer.h>

const int header_chars = 2;
CircularBuffer<char, 2> buff;

void loop()
{
    // Sliding window on incoming serial data
    int n = Serial.available();
    if (n == 0) return;
 
    if (buff.size() == header_chars) {
        bool ret = buff.push(Serial.read());    // Shift left, read a single character
        assert(ret == false);    
        // According to the circularbuffer implementation, if it's overwriting returns true. Should always overwrite here.
    } else {
        // Fill the header_buffer (1st time)
        while ((buff.size() < header_chars) && (n > 0)) {
            buff.push((char)Serial.read());
            n--;
        }
    }

    // Compare
    if ((buff.first() == 'D') && (buff.last() == 'B')) {Serial.println("GOT IT!");}
}