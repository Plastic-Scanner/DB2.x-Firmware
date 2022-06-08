/*
    Arduino firmware for the DB2.x
    Run with: 
        pio run --target upload && pio device monitor
*/
#include "assert.h"
#include "cli.h"
#include "ads1256.h"
#include "tlc59208.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

ADS1256 adc;

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    adc.begin();

    Serial.println("PlasticScanner is initialized!");

    long x = adc.read_channel();
    Serial.println(x);
}

void loop()
{
}