#include "ads1256.h"
#include "ads1256_regmap.h"
#include <Arduino.h>
#include <SPI.h>

#include "assert.h"

static const uint8_t CS   = 10;
static const uint8_t DRDY = 5;
static const uint32_t CLKSPEED = 1000000;   // 1 MHz 

static void send_command(uint8_t cmd)
{
    SPI.beginTransaction(SPISettings(CLKSPEED, MSBFIRST, SPI_MODE1));
    digitalWrite(CS, LOW);
    SPI.transfer(cmd);
    digitalWrite(CS, HIGH);
    SPI.endTransaction();
}

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

ADS1256::ADS1256()
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
    // assert(0);  // DEBUG
    return id;
}

long ADS1256::read_channel()
{
    // Check DRDY pin
    send_command(RDATA);
    uint8_t high=0, mid=0, low=0;
    high = SPI.transfer(NOP);
    mid = SPI.transfer(NOP);
    low = SPI.transfer(NOP);
    uint32_t value = ((uint32_t)high << 16) + ((uint32_t)mid << 8) + ((uint32_t)low);
    return value;
}