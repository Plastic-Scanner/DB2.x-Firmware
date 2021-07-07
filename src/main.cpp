/*
    Arduino firmware for the breakoutboard
    Run with: 
        pio run --target upload && pio device monitor
*/

#include "assert.h"
#include "ads1256.h"
#include "led.h"
#include <Arduino.h>
#include <SPI.h>

ADS1256 adc;
// Led leds[] = {
//     Led(3),
//     Led(4),
// };

void setup()
{
    Serial.begin(9600);
    Serial.println("Initializing...");
    SPI.begin();
    adc.begin();

    // Initialize LEDs
    // for (Led& l : leds) {
        // l.begin();
    // }
    Serial.println("PlasticScanner is initialized!");

}

void loop()
{
    // for (Led& l : leds) {
    //     l.toggle();
    // }

    int id = 0;
    id = adc.read_id();
    Serial.print("ID: ");
    Serial.println(id);
    
    long val = 0;
    val = adc.read_channel();
    Serial.print("channel: ");
    Serial.println(val);

    delay(100);
}