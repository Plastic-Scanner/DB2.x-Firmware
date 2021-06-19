#ifndef LED_H
#define LED_H

#include "ads1256.h"

class Led {
public:
    Led(ADS1256 &adc) : adc(adc) {};
    void begin();

private:
    ADS1256 &adc;
};


#endif // LED_H