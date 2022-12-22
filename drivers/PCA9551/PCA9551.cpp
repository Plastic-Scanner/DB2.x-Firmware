#include "PCA9551.h"
#include "Wire.h"

PCA9551::PCA9551(byte address)
{
    _address = address;
}

uint8_t PCA9551::setLedState(uint8_t ledIndex, uint8_t state)
{
    // Only 7 leds per driver
  	if(ledIndex > 7) return 4;

    // LS0: 0, 1, 2, 3
    // LS1: 4, 5, 6, 7
    byte ledRegister = ledIndex / 4 > 0 ? LS_1 : LS_0;

    // Default: turn all leds off
    byte ledState = ALL_LED_OFF;

    // LED 0 ->  0, 1
    // LED 1 -> 2, 3
    // LED 2 -> 4, 5
    // LED 3 -> 6, 7
    for (int i = 3; i >= 0; i--){
		ledState = (ledState << 2) | (i == ledIndex % 4 ? state : LED_OFF);
    }

   	return _write(ledRegister, ledState);
}

void PCA9551::setPWM0(uint8_t value)
{
  _write(PWM_0, value);
}

void PCA9551::setPWM1(uint8_t value)
{
  _write(PWM_1, value);
}

void PCA9551::setPSC0(uint8_t value){
  _write(FREQ_PSC0, value);
}

void PCA9551::setPSC1(uint8_t value){
  _write(FREQ_PSC1, value);
}

void PCA9551::turnAllOff()
{
    // 0x55 => 01 01 01 01
    _write(LS_0, ALL_LED_OFF);
    _write(LS_1, ALL_LED_OFF);
}

void PCA9551::turnAllOn()
{
  // 0x00 => 00 00 00 00
  _write(LS_0, ALL_LED_ON);
  _write(LS_1, ALL_LED_ON);
}

uint8_t PCA9551::_write(byte LS, byte value)
{
    Wire.beginTransmission(_address);
    Wire.write(LS);
    Wire.write(value);
    return Wire.endTransmission();
}