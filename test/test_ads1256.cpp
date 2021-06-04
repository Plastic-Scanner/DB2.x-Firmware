#include <Arduino.h>
#include <unity.h>
#include "ads1256.h"
#include <SPI.h>

void test_read_id()
{

}


void setup()
{
    UNITY_BEGIN();
    SPI.begin();
    ADS1256 ads1256;
    UNITY_END();
}