#include "ads1256.h"
#include <unity.h>
#include <SPI.h>
#include <Arduino.h>

void test_read_id()
{
    SPI.begin();
    ADS1256 adc;
    adc.begin();
    for (int i=0; i<5; i++) {
        TEST_ASSERT_EQUAL_INT(3, adc.read_id());
    }
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_read_id);
    UNITY_END();
}