/*
    Arduino firmware for the breakoutboard
    Run with: 
        pio run --target upload && pio device monitor
*/

#include "assert.h"
#include "ADS1256.h"
#include "led.h"
#include <Arduino.h>
#include <SPI.h>

static const int CLKSPEED_MHZ = 8;
static const int VREF = 2.5;

ADS1256 adc(CLKSPEED_MHZ, VREF, false);

void setup()
{
    Serial.begin(9600);
    Serial.println("Initializing...");
    SPI.begin();
    adc.begin(ADS1256_DRATE_30000SPS,ADS1256_GAIN_1,false); 
    adc.setChannel(0,1);
    Serial.println("PlasticScanner is initialized!");
}

void loop()
{
    adc.waitDRDY();
    float val = adc.readCurrentChannel();
  
    Serial.print("channel: ");
    Serial.println(val, 10);

    delay(100);
}