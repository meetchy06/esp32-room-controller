#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  delay(1000);
  Serial.println("starting i2c scan");
}

void loop() {
  int count = 0;

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("device found at 0x");

      if (address < 16) {
        Serial.print("0");
      }

      Serial.println(address, HEX);
      count++;
    }
  }

  Serial.print("devices found: ");
  Serial.println(count);
  Serial.println();

  delay(5000);
}
