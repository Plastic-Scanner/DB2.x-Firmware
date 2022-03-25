/*
    Arduino firmware for the DB2.x
    Run with: 
        pio run --target upload && pio device monitor
*/
#include "assert.h"
#include "cli.h"
#include <Arduino.h>

Cli cli;        // Should be a singleton

void dummy(int argc, char *argv[])
{
    Serial.println("Executing function");
}

void setup()
{
    Serial.begin(9600);
    cli.begin([
        {"scan", scan, "Performs a scanning sequence, for each LED: turn LED on, measure ADC, turn LED off"},
        {"adc", adc, "Read ADC value"},
        {"led", led, "Turn LED on or off. Usage: led <number> <on/off>"},
        {"help", help, "Show help"}
    ]);
}

void loop()
{
    cli.handle();
}

