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
TLC59208 ledctrl;

void setup()
{
    Serial.begin(9600);
    Serial.println("Initializing...");
    SPI.begin();
    Wire.begin();

    // adc.begin(ADS1256_DRATE_30000SPS,ADS1256_GAIN_1,false); 
    // adc.setChannel(0,1);
    
    ledctrl.begin();
    Serial.println("PlasticScanner is initialized!");

    ledctrl.ledOn(2);
}

void loop()
{

}