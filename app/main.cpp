/*
    Arduino firmware for the DB2.x
    Run with: 
        pio run --target upload && pio device monitor
*/
#include "assert.h"
#include "command.h"
#include "ADS1256.h"
#include "tlc59208.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

static const int CLKSPEED_MHZ = 8;
static const float VREF = 2.5;
static const int N_LEDS = 8;        // TODO: reorganize this duplicated constant @tlc

ADS1256 adc(CLKSPEED_MHZ, VREF, false);
TLC59208 ledctrl;
Command commands;


void scan()
{
    float readings[8] = {0};
    for (int i=0; i<8; i++) {
        ledctrl.on(i);
        adc.waitDRDY(); 
        readings[i] = adc.readCurrentChannel();
        ledctrl.off(i);
    }

    for (int i=0; i<8; i++) {
        Serial.print(readings[i], 4);
        Serial.print('\t');
    }
    Serial.println();
}

void read_adc()
{
    adc.waitDRDY(); 
    float val = adc.readCurrentChannel();
    Serial.println(val , 10);
}

void ledon(int channel)
{
    if (channel >= 0 && channel < N_LEDS) ledctrl.on(channel);
    else Serial.println("LEDON channel out of range");
}

void ledoff(int channel)
{
    if (channel >= 0 && channel < N_LEDS) ledctrl.off(channel);
    else Serial.println("LEDOFF channel out of range");
}

void unknown_command()
{
    Serial.println("Unknown command");
}


void setup()
{
    Serial.begin(9600);
    SPI.begin();
    Wire.begin();
    ledctrl.begin();
    adc.begin(ADS1256_DRATE_30000SPS,ADS1256_GAIN_1,false); 
    commands.begin(     // set callback functions for each command
        &scan,
        &read_adc,
        &ledon,
        &ledoff,
        &unknown_command
    );

    adc.setChannel(0,1);    // differential ADC reading 
    Serial.println("PlasticScanner is initialized!");
}

void loop()
{
    commands.handle();
}

