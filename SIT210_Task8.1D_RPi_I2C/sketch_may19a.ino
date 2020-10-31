#include <Wire.h>
#define SLAVE_ADDRESS 0x08

long randomNo;

void setup() 
{
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(sendData);
}
void loop() { }

void sendData()
{
  randomNo = random(100);
  Wire.write(randomNo);
}
