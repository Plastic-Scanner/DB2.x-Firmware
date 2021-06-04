#include <Arduino.h>
#include <SPI.h>
#include <ads1256.h>        // Exact model defined inside here, stolen from the library

void setup()
{
    Serial.begin(9500);
    Serial.println("ADC-Arduino test started");

    SPI.begin();
    ADS1256 ads1256;
    Serial.println("Reading chip ID");
    int id = ads1256.read_id();
    Serial.println(id);
}

void loop()
{
}