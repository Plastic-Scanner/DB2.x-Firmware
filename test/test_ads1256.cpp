#include "ads1256.h"
#include <unity.h>
#include <SPI.h>
#include <Arduino.h>

void test_read_id()
{
    SPI.begin();
    ADS1256 ads1256;
    for (int i=0; i<5; i++) {
        TEST_ASSERT_EQUAL_INT(15, ads1256.read_id());
    }
}

void test_assert()
{
    SPI.begin();
    ADS1256 ads1256;
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_read_id);
    RUN_TEST(test_assert);
    UNITY_END();
}