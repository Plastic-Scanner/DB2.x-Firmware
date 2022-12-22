/**
 * PCA9551.h - Arduino library to interface with the PCA9551
 * LED driver. Supports up to 8 leds per driver. Communicates
 * over i2c bus.
 */
#ifndef PCA9551_h
#define PCA9551_h

// All possible i2c address this driver might have
#define PCA9551_ADDR_1 0x60
#define PCA9551_ADDR_2 0x61
#define PCA9551_ADDR_3 0x62
#define PCA9551_ADDR_4 0x63
#define PCA9551_ADDR_5 0x64
#define PCA9551_ADDR_6 0x65
#define PCA9551_ADDR_7 0x66
#define PCA9551_ADDR_8 0x67

// LED Select Registers
#define LS_0 0x05
#define LS_1 0x06

// Frequency Prescalers
#define FREQ_PSC0 0x01
#define FREQ_PSC1 0x03

// PWM registers
#define PWM_0 0x02
#define PWM_1 0x04

// LED states
#define LED_ON 0x00 // 00
#define LED_OFF 0x01 // 01
#define LED_BLINK_0 0b10 // 10
#define LED_BLINK_1 0b11 // 11

// Helper LED states
#define ALL_LED_OFF 0x55 // 0x55 = 01 01 01 01
#define ALL_LED_ON 0x00 // 0x00 = 00 00 00 00

#include "Arduino.h"
#include "Wire.h"

class PCA9551
{
  public:
    PCA9551(byte address);

    void turnAllOn();
    void turnAllOff();

    uint8_t setLedState(uint8_t ledIndex, uint8_t state);

    void setPWM0(uint8_t value);
    void setPWM1(uint8_t value);

    void setPSC0(uint8_t value);
    void setPSC1(uint8_t value);

    uint8_t _write(byte LS, byte value);
  private:
    uint8_t _address;
};

#endif