#include "ads1256.h"
#include <unity.h>
#include <SPI.h>
#include <Arduino.h>

void test_read_id()
{
    SPI.begin();
    ADS1256 ads1256;
    int id = ads1256.read_id();
    TEST_ASSERT_EQUAL_INT(15, id);
}


void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_read_id);
    UNITY_END();
}

void loop() {}