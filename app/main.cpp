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

Command cmd;

void setup()
{
    Serial.begin(9600);
    cmd.begin();
    Serial.println("PlasticScanner is initialized!");
}

void loop()
{
    cmd.handle();
}

