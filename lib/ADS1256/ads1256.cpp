#include "ads1256.h"
#include "ads1256_regmap.h"
#include <Arduino.h>
#include <SPI.h>

static const uint8_t CS   = 10;
static const uint8_t DRDY = 5;
static const uint32_t CLKSPEED = 1000000;   // 1 MHz 

static uint8_t read_register(uint8_t reg)
{
    SPI.beginTransaction(SPISettings(CLKSPEED, MSBFIRST, SPI_MODE1));
    digitalWrite(CS, LOW);
    SPI.transfer(RREG | reg);   // 1st command byte (register address)
    SPI.transfer(0x00);         // 2nd command byte (no.registers to read == 1)
    delayMicroseconds(10);      // do I need this?
    uint8_t rx_data = SPI.transfer(NOP);
    delayMicroseconds(10);      // do I need this?
    digitalWrite(CS, HIGH);
    SPI.endTransaction();
    return rx_data;
}

void ADS1256::init()
{
    // Initialize pins
    pinMode(CS, OUTPUT);
    pinMode(DRDY, INPUT);
    digitalWrite(CS, HIGH);     // De-assert CS line
    // assume that SPI.begin() has been called
}


int ADS1256::read_id()
{
    uint8_t id = read_register(STATUS) >> 4;
    // assert((r >> 4) == id);      // ID should be 15 (decimal)
    return id;
}
