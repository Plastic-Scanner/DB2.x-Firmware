#include <Arduino.h>
#include <SPI.h>
#include <ads1256.h>        // Exact model defined inside here, stolen from the library

ADS1256 ads1256;

void setup()
{
    Serial.begin(9500);
    Serial.println("ADC-Arduino test started");

    SPI.begin();
    ads1256.init();
}

void loop()
{
    Serial.println("Reading chip ID");
    int id = ads1256.read_id();
    Serial.println(id);
}