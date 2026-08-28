
#include <Wire.h>
#include <BH1750.h>
#include <RCSwitch.h>

#include "config.h"

BH1750 lightMeter;
RCSwitch transmitter;

enum class DeviceState {
  Unknown,
  Off,
  On
};

DeviceState lamp1State = DeviceState::Unknown;
DeviceState lamp2State = DeviceState::Unknown;
DeviceState adjustableLampState = DeviceState::Unknown;

unsigned long lastSensorRead = 0;
unsigned long lastLamp1Command = 0;
unsigned long lastLamp2Command = 0;
unsigned long lastAdjustableCommand = 0;

void sendRF(const RFCode& code) {
  if (code.value == 0) {
    Serial.println("rf code not configured");
    return;
  }

  transmitter.setProtocol(code.protocol);
  transmitter.setPulseLength(code.pulse);
  transmitter.setRepeatTransmit(10);
  transmitter.send(code.value, code.bits);
}

void pulseRemote(int pin) {
  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
}

bool cooldownReady(unsigned long lastCommand) {
  return millis() - lastCommand >= COMMAND_COOLDOWN;
}

void setLamp1(bool on) {
  DeviceState target = on ? DeviceState::On : DeviceState::Off;

  if (lamp1State == target || !cooldownReady(lastLamp1Command)) {
    return;
  }

  sendRF(on ? LAMP1_ON : LAMP1_OFF);

  lamp1State = target;
  lastLamp1Command = millis();
}

void setLamp2(bool on) {
  DeviceState target = on ? DeviceState::On : DeviceState::Off;

  if (lamp2State == target || !cooldownReady(lastLamp2Command)) {
    return;
  }

  sendRF(on ? LAMP2_ON : LAMP2_OFF);

  lamp2State = target;
  lastLamp2Command = millis();
}

void setAdjustableLamp(bool on) {
  DeviceState target = on ? DeviceState::On : DeviceState::Off;

  if (adjustableLampState == target ||
      !cooldownReady(lastAdjustableCommand)) {
    return;
  }

  pulseRemote(on ? REMOTE_ON_PIN : REMOTE_OFF_PIN);

  adjustableLampState = target;
  lastAdjustableCommand = millis();
}

void updateLighting(float lux) {
  if (lux <= LIGHT_ON_THRESHOLD) {
    setLamp1(true);
    setLamp2(true);
    setAdjustableLamp(true);
  }

  if (lux >= LIGHT_OFF_THRESHOLD) {
    setLamp1(false);
    setLamp2(false);
    setAdjustableLamp(false);
  }
}

void handleSerial() {
  if (!Serial.available()) {
    return;
  }

  char command = Serial.read();

  switch (command) {
    case '1':
      setLamp1(true);
      break;

    case '2':
      setLamp1(false);
      break;

    case '3':
      setLamp2(true);
      break;

    case '4':
      setLamp2(false);
      break;

    case 'o':
      setAdjustableLamp(true);
      break;

    case 'f':
      setAdjustableLamp(false);
      break;

    case 'u':
      pulseRemote(BRIGHTNESS_UP_PIN);
      break;

    case 'd':
      pulseRemote(BRIGHTNESS_DOWN_PIN);
      break;
  }
}

void setup() {
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!lightMeter.begin()) {
    Serial.println("bh1750 not found");
  }

  transmitter.enableTransmit(RF_TX_PIN);

  pinMode(REMOTE_ON_PIN, OUTPUT);
  pinMode(REMOTE_OFF_PIN, OUTPUT);
  pinMode(BRIGHTNESS_UP_PIN, OUTPUT);
  pinMode(BRIGHTNESS_DOWN_PIN, OUTPUT);

  digitalWrite(REMOTE_ON_PIN, LOW);
  digitalWrite(REMOTE_OFF_PIN, LOW);
  digitalWrite(BRIGHTNESS_UP_PIN, LOW);
  digitalWrite(BRIGHTNESS_DOWN_PIN, LOW);

  Serial.println("room controller started");
}

void loop() {
  handleSerial();

  if (millis() - lastSensorRead < SENSOR_INTERVAL) {
    return;
  }

  lastSensorRead = millis();

  float lux = lightMeter.readLightLevel();

  Serial.print("light: ");
  Serial.print(lux);
  Serial.println(" lux");

  updateLighting(lux);
}
