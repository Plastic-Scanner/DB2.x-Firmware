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

void setup()
{
    Serial.begin(9600);
    Serial.println("Initializing...");
    SPI.begin();
    adc.begin();
    Serial.println("PlasticScanner is initialized!");

    int id = 0;
    id = adc.read_id();
    Serial.print("ID: ");
    Serial.println(id);
}

void loop()
{
    long val = 0;
    val = adc.read_channel();
    Serial.print("channel: ");
    Serial.println(val);

    delay(500);
}