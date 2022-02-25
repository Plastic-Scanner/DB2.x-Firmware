/*
    Arduino firmware for the DB2.x
    Run with: 
        pio run --target upload && pio device monitor
*/
#include "command.h"
#include "assert.h"
#include <Arduino.h>

Command commands;

void setup()
{
    Serial.begin(9600);
    Serial.println("Initialized");
    commands.begin();
}



void loop()
{
    commands.handle();
}