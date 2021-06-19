/*
    Arduino firmware for the breakoutboard
    Run with: 
        pio run --target upload && pio device monitor
*/

#include "assert.h"
#include "ads1256.h"
#include <Arduino.h>
#include <SPI.h>

ADS1256 adc;

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    adc.begin();
    Serial.println("PlasticScanner is initialized!");
}

void loop()
{
    Serial.println(adc.read_channel());
    delay(500);
}