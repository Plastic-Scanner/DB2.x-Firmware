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
Led led(2);

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    adc.begin();
    led.begin();

    Serial.println("PlasticScanner is initialized!");
}

void loop()
{
    led.toggle();
    delay(1000);
    Serial.println("loop");
}