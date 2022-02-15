#include "tlc59208.h"
#include "assert.h"
#include <Arduino.h>
#include <Wire.h>

static const int RESET = 0;
static const int ADDR  = 0x00;
static const int N_OUTPUTS = 8;

static void reset()
{
    digitalWrite(RESET, LOW);
    delay(1);
    digitalWrite(RESET, HIGH);
    delay(1);
}


void TLC59208::begin()
{
    pinMode(RESET, OUTPUT);
    digitalWrite(RESET, HIGH);
    
    reset();
}

void TLC59208::ledOn(int output)
{
    assert((output >= 0) && (output < N_OUTPUTS));
    Wire.beginTransmission(ADDR);
    Wire.write(0x0C);       // LEDOUT0 register
    // Wire.write((uint8_t)0x01 << (2*output));
    Wire.write(0xFFu);
    Wire.endTransmission();
}