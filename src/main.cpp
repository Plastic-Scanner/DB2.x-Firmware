/*
    Arduino firmware for the DB2.x
    Run with: 
        pio run --target upload && pio device monitor
*/
#include "assert.h"
#include "ADS1256.h"
#include "tlc59208.h"
#include "led.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

static const int CLKSPEED_MHZ = 8;
static const float VREF = 2.5;

ADS1256 adc(CLKSPEED_MHZ, VREF, false);
TLC59208 leds;

void setup()
{
    Serial.begin(9600);
    Serial.println("Initializing...");
    SPI.begin();
    Wire.begin();

    // adc.begin(ADS1256_DRATE_30000SPS,ADS1256_GAIN_1,false); 
    // adc.setChannel(0,1);
    
    leds.begin();
    Serial.println("PlasticScanner is initialized!");

    for (int i=0; i<8; i++) {
        leds.on(i);
        delay(500);
        leds.off(i);
    }
}

void loop()
{

}