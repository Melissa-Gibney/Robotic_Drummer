// Teensy LED over I2C
// 3/27/24

#include <Arduino.h>
#include <Wire.h>

#define SDA 18
#define SCL 19

#define LED 33

#define I2CADDRESS 0x3A

void flash();

void setup() {
  // put your setup code here, to run once:
  Wire.begin(I2CADDRESS);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Wire.onRequest(flash);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void flash()
{
  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(LED, LOW);

}