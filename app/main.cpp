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
#include <SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h>
NAU7802 nau;
/////////////////////////


///////////////////LED DRIVER////////////////////////////
// If you are using the original Texas instruments led driver please use the following include
// If you are using the PCA9551 led driver (which is often more in stock, please use the that library include
// IMPORTANT: also change it at line 35, 41 and line 80
// #include "tlc59208.h"
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
        delay(10);

        // skip the first 10 readings
        for (uint8_t i=0; i<15; i++) {
            while (! nau.available()) delay(1);
            nau.getReading();
        }
        //ADC
        //adc.waitDRDY();
        //readings[i] = adc.readCurrentChannel();
        //float val = 0 ;
        // skit the first 2 readings

        // for (uint8_t i=0; i<2; i++) {
        //     while (! nau.available()) delay(1);
        //     readings[i] = readings[i] + nau.getReading();
        // }
        while (! nau.available()) delay(1);
        readings[i] = nau.getAverage(15);
        // readings[i] = nau.getReading();         
        //delay(50);
        //LED DRIVER: For TLC59208 choose the ledctrl, for PCA9551 choose ledDriver////////////////////
        //ledctrl.off(i);
        ledDriver.setLedState(i, LED_OFF);
        //delay(50);
    }

    for (int i=0; i<8; i++) {
        Serial.print(readings[i], 1);
        Serial.print('\t');
    }
    Serial.println();
}

void read_adc(int argc, char *argv[])
{
    //ADC
    //adc.waitDRDY();
    //float val = adc.readCurrentChannel();
    long val = 0 ;
    for (uint8_t i=0; i<10; i++) {
        while (! nau.available()) delay(1);
        nau.getReading();
    }
    for (uint8_t i=0; i<10; i++) {
        while (! nau.available()) delay(1);
        val = val + nau.getReading();
    }
    // while (! nau.available()) {
    //     delay(1);
    // }
    //float val = nau.getReading();  

    Serial.println(val , 1);
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
        //state == true ? ledctrl.on(num) : ledctrl.off(num);
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
    Wire.setClock(400000);
    
    //ledctrl.begin();
    //ADC
    // SPI.begin();
    // adc.begin(ADS1256_DRATE_30000SPS,ADS1256_GAIN_1,false); 
    // adc.setChannel(0,1);    // differential ADC reading 
    if (! nau.begin()) {
        Serial.println("Failed to find NAU7802");
    }
    // Serial.println("Found NAU7802");
    // Take 10 readings to flush out readings
    for (uint8_t i=0; i<10; i++) {
        while (! nau.available()) delay(1);
        nau.getReading();
    }
    nau.setLDO(3.3);
    nau.setGain(NAU7802_GAIN_128);
    nau.setSampleRate(NAU7802_SPS_320); //Increase to max sample rate
    nau.calibrateAFE(); //Re-cal analog front end when we change gain, sample rate, or channel 
    
    // Serial.print("Zero offset: ");
    // Serial.println(nau.getZeroOffset());
    // Serial.print("Calibration factor: ");
    // Serial.println(nau.getCalibrationFactor());
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

