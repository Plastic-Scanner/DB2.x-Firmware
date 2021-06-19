/*
    LEDs are controlled by the multiplexer (74HC238PW, U6 on the PCB)
    Address pins are driven through the ADC's I/O pins
    Strobe pin is connected directly to the MCU
*/
#include "led.h"
#include "ads1256.h"
#include "ads1256_regmap.h"
#include "assert.h"

#define STROBE      4   // D4 pin

void Led::begin()
{
    // Initialize ADC's GPIOs as outputs
    adc.write_register(IO, 0x00);
    assert(adc.read_register(IO) == 0x00);
}