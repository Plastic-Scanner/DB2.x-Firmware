#include <ADS1256.h>
#include <SPI.h>

float clockMHZ = 8.0;
float vRef = 2.5;

ADS1256 adc(clockMHZ,vRef,false);

float sensor1;


void setup()
{
  Serial.begin(9600);
  Serial.println("Starting ADC");

//   adc.begin(ADS1256_DRATE_30000SPS,ADS1256_GAIN_1,false); 
  adc.begin();
  Serial.println("ADC Started");

  adc.setChannel(0,1);
}

void loop()
{ 
  adc.waitDRDY();
  sensor1 = adc.readCurrentChannel();
  Serial.println(sensor1, 10);
}