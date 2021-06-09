#include "assert.h"
#include "ads1256.h"
#include <Arduino.h>
#include <SPI.h>

ADS1256 adc;

void setup()
{
    Serial.begin(9500);
    Serial.println("PlasticScanner is alive!");

    SPI.begin();
    adc.begin();
}

void loop()
{
    Serial.println(adc.read_id());
    delay(250);
}