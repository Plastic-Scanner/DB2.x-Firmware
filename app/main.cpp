/*
    Arduino firmware for the DB2.x
    Run with: 
        pio run --target upload && pio device monitor
*/
#include <Arduino.h>

#include "assert.h"
#include "cli.h"
///////////////////ADC DRIVER////////////////////////////
// #include "ADS1256.h"
// #include <SPI.h>
// static const int CLKSPEED_MHZ = 8;
// static const float VREF = 2.5;
// ADS1256 adc(CLKSPEED_MHZ, VREF, false);

#include <Adafruit_NAU7802.h>
Adafruit_NAU7802 nau;
/////////////////////////


///////////////////LED DRIVER////////////////////////////
// If you are using the original Texas instruments led driver please use the following include
// If you are using the PCA9551 led driver (which is often more in stock, please use the that library include
// IMPORTANT: also change it at line 35, 41 and line 80
//#include "tlc59208.h"
// TLC59208 ledctrl;
#include "PCA9551.h"
PCA9551 ledDriver = PCA9551(PCA9551_ADDR_1);
/////////////////////////


#include <Wire.h>
Cli cli;

void scan(int argc, char *argv[])
{
    float readings[8] = {0};
    for (int i=0; i<8; i++) {
        //LED DRIVER: For TLC59208 choose the ledctrl, for PCA9551 choose ledDriver////////////////////
        // ledctrl.on(i);
        ledDriver.setLedState(i, LED_ON);
        delay(5);

        //ADC
        //adc.waitDRDY();
        //readings[i] = adc.readCurrentChannel();
        while (! nau.available()) {
            delay(1);
        }
        readings[i] = nau.read();         
        
        //LED DRIVER: For TLC59208 choose the ledctrl, for PCA9551 choose ledDriver////////////////////
        // ledctrl.off(i);
        ledDriver.setLedState(i, LED_OFF);
    }

    for (int i=0; i<8; i++) {
        Serial.print(readings[i], 5);
        Serial.print('\t');
    }
    Serial.println();
}

void read_adc(int argc, char *argv[])
{
    //ADC
    //adc.waitDRDY();
    //float val = adc.readCurrentChannel();
    while (! nau.available()) {
        delay(1);
    }
    float val = nau.read();  

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
    
    //ADC
    // SPI.begin();
    // adc.begin(ADS1256_DRATE_30000SPS,ADS1256_GAIN_1,false); 
    // adc.setChannel(0,1);    // differential ADC reading 
    if (! nau.begin()) {
        Serial.println("Failed to find NAU7802");
    }
    Serial.println("Found NAU7802");
    nau.setLDO(NAU7802_3V0);
    nau.setGain(NAU7802_GAIN_128);
    nau.setRate(NAU7802_RATE_10SPS);
    // Take 10 readings to flush out readings
    for (uint8_t i=0; i<10; i++) {
        while (! nau.available()) delay(1);
        nau.read();
    }
    while (! nau.calibrate(NAU7802_CALMOD_INTERNAL)) {
        Serial.println("Failed to calibrate internal offset, retrying!");
        delay(1000);
    }
    Serial.println("Calibrated internal offset");

    while (! nau.calibrate(NAU7802_CALMOD_OFFSET)) {
        Serial.println("Failed to calibrate system offset, retrying!");
        delay(1000);
    }
    Serial.println("Calibrated system offset");

    cli.add_command({"scan", scan, "Perform a scan sequence: for each led measure adc value"});
    cli.add_command({"adc", read_adc, "Reads ADC measurement"});
    cli.add_command({"led", led, "Turns an LED <number> on/off <state>.\n\t\t\t\tUsage: led <number> <state>"});
    cli.add_command({"help", help, "Lists all available commands"});
    cli.begin();

    //Serial.println("PlasticScanner is initialized!");
}

void loop()
{
    cli.handle();
}

