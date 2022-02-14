/*
    Arduino firmware for the breakoutboard
    Run with: 
        pio run --target upload && pio device monitor
*/

#include "assert.h"
#include <ADS1256.h>
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
    adc.begin();
    adc.setChannel(0);
    Serial.println("PlasticScanner is initialized!");

    // int id = 0;
    // id = adc.read_id();
    // Serial.print("ID: ");
    // Serial.println(id);
}

void loop()
{
    float val = 0;

    adc.waitDRDY();
    val = adc.readCurrentChannel();
  
    Serial.print("channel: ");
    Serial.println(val);

    delay(500);
}