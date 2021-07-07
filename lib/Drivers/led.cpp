/*
    LEDs are controlled by the multiplexer (74HC238PW, U6 on the PCB)
    Address pins are driven through the ADC's I/O pins
    Strobe pin is connected directly to the MCU
*/
#include "led.h"
#include "assert.h"
#include "Arduino.h"

void Led::begin()
{
    // Initialize LED
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void Led::on()
{
    digitalWrite(_pin, HIGH);
}

void Led::off ()
{
    digitalWrite(_pin, LOW);
}

void Led::toggle()
{
    digitalWrite(_pin, !digitalRead(_pin));
}