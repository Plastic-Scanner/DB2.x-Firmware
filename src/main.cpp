#include "assert.h"
#include "ads1256.h"
#include <Arduino.h>
#include <SPI.h>

int main()
{
    Serial.begin(9500);
    Serial.println("PlasticScanner is alive!");
    Serial.flush();

    // SPI.begin();
    // ADS1256 adc;

    while (1) {
        Serial.println("tick");
        delay(100);
    }
}