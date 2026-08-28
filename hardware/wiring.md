# Wiring

BH1750 light sensor:
VCC -> ESP32 3V3
GND -> ESP32 GND
SDA -> ESP32 GPIO21
SCL -> ESP32 GPIO22
ADDR -> not connected

BME280 sensor:
VCC -> ESP32 3V3
GND -> ESP32 GND
SDA -> ESP32 GPIO21
SCL -> ESP32 GPIO22
CS/CSB -> ESP32 3V3
SDO -> ESP32 GND

433 MHz receiver:
VIN -> ESP32 3V3
GND -> ESP32 GND
DO -> ESP32 GPIO26
second DO -> not connected

433 MHz transmitter:
+ -> ESP32 3V3
- -> ESP32 GND
DAT -> ESP32 GPIO27
EN -> not connected

Optocoupler control pins:
IN1 -> ESP32 GPIO16
IN2 -> ESP32 GPIO17
IN3 -> ESP32 GPIO18
IN4 -> ESP32 GPIO19
GND -> ESP32 GND

Lamp remote:
The original remote remained powered by its own battery.
The optocoupler outputs were connected across the mapped button contacts for:
- power on
- power off
- brightness up
- brightness down
