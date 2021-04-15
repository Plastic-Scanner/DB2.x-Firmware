#include <Arduino.h>
#include <SPI.h>
#include <ads1256.h>        // Exact model defined inside here, stolen from the library

static const int CS   = 10;
static const int DRDY = 5;
static const int CLKSPEED = 1000000;   // 1 MHz 

void setup()
{
    Serial.begin(115200);
    Serial.println("ADC-Arduino test started");

    // Initialize pins
    pinMode(CS, OUTPUT);
    pinMode(DRDY, INPUT);
    digitalWrite(CS, HIGH);     // De-assert CS line

    // Initialize SPI
    SPI.begin();
}

void loop()
{
    // Read ADC ID
    // Serial.println("Transfer start");

    SPI.beginTransaction(SPISettings(CLKSPEED, MSBFIRST, SPI_MODE1));
    digitalWrite(CS, LOW);
    
    SPI.transfer(RREG | STATUS);    // 1st command byte (register address)
    SPI.transfer(0x00);             // 2nd command byte (no.registers to read)
    delayMicroseconds(10);  // do I need this?
    uint8_t rx_data = SPI.transfer(NOP);
    delayMicroseconds(10);  // do I need this?

    digitalWrite(CS, HIGH);
    SPI.endTransaction();

    // Serial.println("Transfer completed: ");
    Serial.println(rx_data, BIN);

    delay(1000);
}