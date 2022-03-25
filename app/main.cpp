/*
    Arduino firmware for the DB2.x
    Run with: 
        pio run --target upload && pio device monitor
*/
#include "assert.h"
#include "cli.h"
#include <Arduino.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

Cli cli;

void dummy(int argc, char *argv[])
{
    Serial.println("Executing function");
}

void setup()
{
    Serial.begin(9600);
    
    Cli::Command cmdlist[] = {
        {"dummy", dummy, "Dummy command which prints something"},
        {"help", cli.list_commands, "Prints a list of available commands"},
    };
    cli.begin(cmdlist, ARRAY_SIZE(cmdlist));
}

void loop()
{
    cli.handle();
}

