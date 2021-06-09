#include <Arduino.h>
#include <SPI.h>
#include "assert.h"
#include "ads1256.h"

int main()
{
    Serial.begin(9500);
    Serial.println("PlasticScanner is alive!");
    SPI.begin();
    ADS1256 adc;

    Serial.println("Finished!");
    Serial.flush();
    while(1);
}