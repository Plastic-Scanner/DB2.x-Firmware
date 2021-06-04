#include <Arduino.h>
#include <unity.h>
#include "ads1256.h"
#include <SPI.h>

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