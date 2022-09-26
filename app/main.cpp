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
#include <Adafruit_AS7341.h>

Adafruit_AS7341 as7341;

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

void vis(int argc, char *argv[])
{
    as7341.setLEDCurrent(4); // 4mA
    as7341.enableLED(true);
    delay(5);
    uint16_t readings[12];
    if (!as7341.readAllChannels(readings)){
    Serial.println("Error reading all channels!");
    return;
    }
    for (int i=0; i<10; i++) {
        float x = float(readings[i])/500;
        Serial.print(x, 6);
        Serial.print('\t');
    }
    Serial.println();
  as7341.enableLED(false);


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
    Serial.begin(115200);
    SPI.begin();
    Wire.begin();
    ledctrl.begin();
    adc.begin(ADS1256_DRATE_30000SPS,ADS1256_GAIN_1,false); 
    adc.setChannel(0,1);    // differential ADC reading 
    
    // start as7341 stuff
    if (!as7341.begin()){
        Serial.println("Could not find AS7341");
        while (1) { delay(10); }
    }
    
    as7341.setATIME(100);
    as7341.setASTEP(999);
    as7341.setGain(AS7341_GAIN_1X);
    // end as7241 stuff

    cli.add_command({"scan", scan, "Perform a scan sequence: for each led measure adc value"});
    cli.add_command({"adc", read_adc, "Reads ADC measurement"});
    cli.add_command({"led", led, "Turns an LED <number> on/off <state>.\n\t\t\t\tUsage: led <number> <state>"});
    cli.add_command({"help", help, "Lists all available commands"});
    cli.add_command({"vis", vis, "Perform a scan of visual spectrum with as7341"});
    cli.begin();

    //Serial.println("PlasticScanner is initialized!");
}

void loop()
{
    cli.handle();
}