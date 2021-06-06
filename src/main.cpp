#include <Arduino.h>
#include <SPI.h>
#include "assert.h"
#include "ads1256.h"

int main()
{
    Serial.begin(9500);
    Serial.println("Misterious assert fail example");
    Serial.flush();
    assert(false);      // [OK] Assert message should be printed completely, then get stuck
    
    // However, causing an assert to fail within the ads1256 class will not work (assert msg not printed fully). Why is that?
    ADS1256 adc;
    // adc.assert_debug(true);

    Serial.println("Finished!");
    Serial.flush();
}