/*
    Arduino firmware for the breakoutboard
    Run with: 
        pio run --target upload && pio device monitor
*/

#include "assert.h"
#include "ads1256.h"
#include "led.h"
#include <Arduino.h>
#include <SPI.h>

ADS1256 adc;
Led leds[] = {
    Led(2),
    Led(3),
    Led(8)
};

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    adc.begin();

    // Initialize LEDs
    for (Led& l : leds) {
        l.begin();
    }
    Serial.println("PlasticScanner is initialized!");
}

void loop()
{
    for (Led& l : leds) {
        l.toggle();
    }
    delay(1000);
}