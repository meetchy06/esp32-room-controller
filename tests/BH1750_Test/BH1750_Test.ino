#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  if (lightMeter.begin()) {
    Serial.println("bh1750 ready");
  } else {
    Serial.println("bh1750 not found");
  }
}

void loop() {
  float lux = lightMeter.readLightLevel();

  Serial.print("light: ");
  Serial.print(lux);
  Serial.println(" lux");

  delay(1000);
}
