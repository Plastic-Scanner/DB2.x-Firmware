#include "tlc59208.h"
#include "assert.h"
#include <Arduino.h>
#include <Wire.h>

static const int RESET = 2;
static const int ADDR  = 0x20;
static const int N_OUTPUTS = 8;

static void reset()
{
    digitalWrite(RESET, LOW);
    delay(1);
    digitalWrite(RESET, HIGH);
    delay(1);
}


static void setBrightness(int output, int percents)
{
    assert((output >= 0) && (output < N_OUTPUTS));
    assert((percents >= 0) && (percents <=100));

    uint8_t reg = 0x02 + output;
    uint8_t pwm = (percents * 255)/100;
    
    Wire.beginTransmission(ADDR);
    Wire.write(reg);
    Wire.write(pwm);
    Wire.endTransmission();
}

void TLC59208::begin()
{
    pinMode(RESET, OUTPUT);
    digitalWrite(RESET, HIGH);
    
    reset();

    // configure
    Wire.beginTransmission(ADDR);
    Wire.write(0x80);   // Control: auto-increment + register address
    Wire.write(0x81);   // 00h: MODE1
    Wire.write(0x03);   // 01h: MODE2
    Wire.write(0x00);   // 02h: PWM0
    Wire.write(0x00);   // 03h: PWM1
    Wire.write(0x00);   // 04h: PWM2
    Wire.write(0x00);   // 05h: PWM3
    Wire.write(0x00);   // 06h: PWM4
    Wire.write(0x00);   // 07h: PWM5
    Wire.write(0x00);   // 08h: PWM6
    Wire.write(0x00);   // 09h: PWM7
    Wire.write(0xFF);   // 0Ah: GRPPWM
    Wire.write(0x00);   // 0Bh: GRPFREQ
    Wire.write(0xAA);   // 0Ch: LEDOUT0         // LEDs controlled via PWM register
    Wire.write(0xAA);   // 0Dh: LEDOUT1
    Wire.write(0x00);   // 0Eh: SUBADR1
    Wire.write(0x00);   // 0Fh: SUBADR2
    Wire.write(0x00);   // 10h: SUBADR3
    Wire.write(0x00);   // 11h: ALLCALLADR
    Wire.endTransmission();

    setBrightness(1, 100);
    delay(1000);
    setBrightness(1, 50);
    delay(1000);
    setBrightness(1, 0);
}


void TLC59208::ledOn(int output)
{
    assert((output >= 0) && (output < N_OUTPUTS));
    Wire.beginTransmission(ADDR);
    Wire.write(0x02);   // PWM0 register
    Wire.write(0x00);
    Wire.endTransmission();
}