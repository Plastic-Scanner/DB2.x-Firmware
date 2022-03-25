/*
    Arduino firmware for the DB2.x
    Run with: 
        pio run --target upload && pio device monitor
*/
#include "assert.h"
#include "cli.h"
#include <Arduino.h>

Cli cli;

void dummy(int argc, char *argv[])
{
    Serial.println("Executing function");
}

void help(int argc, char *argv[])
{
    cli.list_commands();
}

void setup()
{
    Serial.begin(9600);
    cli.add_command({"dummy", dummy, "Execute a dummy command"});
    cli.add_command({"scan", nullptr, "Perform a scan sequence: for each led measure adc value"});
    cli.add_command({"help", help, "Lists all available commands"});
    cli.begin();
}

void loop()
{
    cli.handle();
}

