/*
    Arduino firmware for the DB2.x
    Run with: 
        pio run --target upload && pio device monitor
*/
#include "assert.h"
#include "cli.h"
#include "ADS1256.h"
#include "tlc59208.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

static const int CLKSPEED_MHZ = 8;
static const float VREF = 2.5;

ADS1256 adc(CLKSPEED_MHZ, VREF, false);
TLC59208 ledctrl;
Cli cli;

void scan(int argc, char *argv[])
{
    float readings[8] = {0};
    for (int i=0; i<8; i++) {
        ledctrl.on(i);
        delay(5);
        adc.waitDRDY(); 
        readings[i] = adc.readCurrentChannel();
        ledctrl.off(i);
    }

    for (int i=0; i<8; i++) {
        Serial.print(readings[i], 5);
        Serial.print('\t');
    }
    Serial.println();
}

void read_adc(int argc, char *argv[])
{
    adc.waitDRDY(); 
    float val = adc.readCurrentChannel();
    Serial.println(val , 5);
}

void led(int argc, char *argv[])
{
    int num;        // Parameter 1: led number [0..7]
    bool state;     // Parameter 2: led state [on/off]
    if (argc != 3) {
        Serial.println("Usage: led <number> <on/off>");
        return;
    }

    // Parameter checking
    bool args_ok = true;
    num = (int)strtol(argv[1], NULL, 10);
    if (num < 0 || num > 7) args_ok = false;
    if      (strcmp(argv[2], "on") == 0) state = true;
    else if (strcmp(argv[2], "off") == 0) state = false;
    else args_ok = false;

    if (args_ok == false) {
        Serial.println("Usage: Usage: led <number> <on/off>");
    } else {
        state == true ? ledctrl.on(num) : ledctrl.off(num);
    }
}

void help(int argc, char *argv[])
{
    cli.list_commands();
}

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    Wire.begin();
    ledctrl.begin();
    adc.begin(ADS1256_DRATE_30000SPS,ADS1256_GAIN_1,false); 
    adc.setChannel(0,1);    // differential ADC reading 

    cli.add_command({"scan", scan, "Perform a scan sequence: for each led measure adc value"});
    cli.add_command({"adc", read_adc, "Reads ADC measurement"});
    cli.add_command({"led", led, "Turns an LED <number> on/off <state>.\n\t\t\t\tUsage: led <number> <state>"});
    cli.add_command({"help", help, "Lists all available commands"});
    cli.begin();

    Serial.println("PlasticScanner is initialized!");
}

void loop()
{
    cli.handle();
}

