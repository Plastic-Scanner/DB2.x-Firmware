#include <Arduino.h>
#include <SPI.h>
#include <ads1256.h>        // Exact model defined inside here, stolen from the library

void setup()
{
    Serial.begin(9500);
    Serial.println("ADC-Arduino test started");

    // Initialization
    SPI.begin();
    ADS1256 ads1256;

    // Read chip ID (should be 15 @decimal)
    Serial.println("Reading chip ID");
    int id = ads1256.read_id();
    Serial.println(id);

    // Read single conversion (channel ??)
    while(true) {
        long reading = ads1256.read_channel();
        Serial.println(reading);
        delay(1000);
    }
}

void loop() {}