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

const int NUM_LEDS = 4;

ADS1256 adc;
// Led leds[] = {
//     Led(1),
//     Led(2),
//     Led(3)
// };
Led a(2);
Led b(3);
Led c(7);

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    adc.begin();
    a.begin();
    b.begin();
    c.begin();
    Serial.println("PlasticScanner is initialized!");
}

void loop()
{
    a.toggle();
    b.toggle();
    c.toggle();
    delay(1000);
    Serial.println("loop");
}