#include <Arduino.h>
#include <SPI.h>
#include <ads1256.h>        // Exact model defined inside here, stolen from the library
#include "assert.h"

int main()
{
    Serial.begin(9500);
    Serial.println("Misterious assert fail example");
    Serial.flush();
    assert(false);
}