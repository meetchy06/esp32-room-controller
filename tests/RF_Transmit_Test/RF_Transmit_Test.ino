#include <RCSwitch.h>

RCSwitch transmitter;

const int transmitterPin = 27;

struct RFCode {
  unsigned long value;
  unsigned int bits;
  unsigned int protocol;
  unsigned int pulse;
};

RFCode lamp1On  = {10828817, 24, 1, 350};
RFCode lamp1Off = {10828820, 24, 1, 350};
RFCode lamp2On  = {10828833, 24, 1, 350};
RFCode lamp2Off = {10828836, 24, 1, 350};

void sendCode(const RFCode& code) {
  if (code.value == 0) {
    Serial.println("rf code not set");
    return;
  }

  transmitter.setProtocol(code.protocol);
  transmitter.setPulseLength(code.pulse);
  transmitter.setRepeatTransmit(10);
  transmitter.send(code.value, code.bits);
}

void setup() {
  Serial.begin(115200);
  transmitter.enableTransmit(transmitterPin);

  Serial.println("1 lamp 1 on");
  Serial.println("2 lamp 1 off");
  Serial.println("3 lamp 2 on");
  Serial.println("4 lamp 2 off");
}

void loop() {
  if (!Serial.available()) {
    return;
  }

  char command = Serial.read();

  switch (command) {
    case '1':
      sendCode(lamp1On);
      break;

    case '2':
      sendCode(lamp1Off);
      break;

    case '3':
      sendCode(lamp2On);
      break;

    case '4':
      sendCode(lamp2Off);
      break;
  }
}
