#pragma once

#include <Arduino.h>

const int SDA_PIN = 21;
const int SCL_PIN = 22;

const int RF_TX_PIN = 27;

const int REMOTE_ON_PIN = 16;
const int REMOTE_OFF_PIN = 17;
const int BRIGHTNESS_UP_PIN = 18;
const int BRIGHTNESS_DOWN_PIN = 19;

const float LIGHT_ON_THRESHOLD = 80.0;
const float LIGHT_OFF_THRESHOLD = 130.0;

const unsigned long SENSOR_INTERVAL = 1000;
const unsigned long COMMAND_COOLDOWN = 3000;

struct RFCode {
  unsigned long value;
  unsigned int bits;
  unsigned int protocol;
  unsigned int pulse;
};

const RFCode LAMP1_ON  = {10828817, 24, 1, 350};
const RFCode LAMP1_OFF = {10828820, 24, 1, 350};

const RFCode LAMP2_ON  = {10828833, 24, 1, 350};
const RFCode LAMP2_OFF = {10828836, 24, 1, 350};
