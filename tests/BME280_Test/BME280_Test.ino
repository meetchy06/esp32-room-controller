#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  bool found = bme.begin(0x76);

  if (!found) {
    found = bme.begin(0x77);
  }

  if (found) {
    Serial.println("bme280 ready");
  } else {
    Serial.println("bme280 not found");
  }
}

void loop() {
  Serial.print("temperature: ");
  Serial.print(bme.readTemperature());
  Serial.println(" c");

  Serial.print("humidity: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();

  delay(2000);
}
