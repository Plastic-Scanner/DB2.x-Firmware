/*
    Arduino firmware for the DB2.x
    Run with: 
        pio run --target upload && pio device monitor
*/
#include "assert.h"
#include "cli.h"

///////////////////LED DRIVER////////////////////////////
// If you are using the original Texas instruments led driver please use the following include
// If you are using the PCA9551 led driver (which is often more in stock, please use the that library include
// IMPORTANT: also change it at line 35, 41 and line 80
//#include "tlc59208.h"
// TLC59208 ledctrl;
#include "PCA9551.h"
PCA9551 ledDriver = PCA9551(PCA9551_ADDR_1);
/////////////////////////
#include <Arduino.h>
#include <Wire.h>

Cli cli;

void scan(int argc, char *argv[])
{
    Serial.println("scan start");
    for (int i=0; i<8; i++) {
        //LED DRIVER: For TLC59208 choose the ledctrl, for PCA9551 choose ledDriver////////////////////
        // ledctrl.on(i);
        ledDriver.setLedState(i, LED_ON);

        delay(10);
        //LED DRIVER: For TLC59208 choose the ledctrl, for PCA9551 choose ledDriver////////////////////
        // ledctrl.off(i);
        ledDriver.setLedState(i, LED_OFF);
    }
    Serial.println("scan done");
    delay(100);
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
        //LED DRIVER: For TLC59208 choose the ledctrl, for PCA9551 choose ledDriver////////////////////
        // state == true ? ledctrl.on(num) : ledctrl.off(num);
        state == true ? ledDriver.setLedState(num, LED_ON) : ledDriver.setLedState(num, LED_OFF);
    }
}

void help(int argc, char *argv[])
{
    cli.list_commands();
}

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    // ledctrl.begin();

    cli.add_command({"scan", scan, "Perform a scan sequence: for each led measure adc value"});
    cli.add_command({"led", led, "Turns an LED <number> on/off <state>.\n\t\t\t\tUsage: led <number> <state>"});
    cli.add_command({"help", help, "Lists all available commands"});
    cli.begin();

    Serial.println("PlasticScanner is initialized!");
}

void loop()
{
    cli.handle();
}

