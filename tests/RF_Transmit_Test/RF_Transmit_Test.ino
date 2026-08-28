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

unsigned long transmissionCount = 0;

void sendCode(const RFCode& code, const char* name) {
  if (code.value == 0) {
    Serial.println("rf code not set");
    return;
  }

  transmitter.setProtocol(code.protocol);
  transmitter.setPulseLength(code.pulse);
  transmitter.setRepeatTransmit(10);

  transmissionCount++;

  unsigned long startTime = micros();

  Serial.println();
  Serial.println("----------------------------");
  Serial.println("rf transmission started");

  Serial.print("command: ");
  Serial.println(name);

  Serial.print("packet number: ");
  Serial.println(transmissionCount);

  Serial.print("value: ");
  Serial.println(code.value);

  Serial.print("bits: ");
  Serial.println(code.bits);

  Serial.print("protocol: ");
  Serial.println(code.protocol);

  Serial.print("pulse length: ");
  Serial.print(code.pulse);
  Serial.println(" us");

  Serial.println("repeats: 10");

  transmitter.send(code.value, code.bits);

  unsigned long elapsed = micros() - startTime;

  Serial.print("send sequence duration: ");
  Serial.print(elapsed);
  Serial.println(" us");

  Serial.println("gpio transmission sequence completed");
  Serial.println("----------------------------");
}

void setup() {
  Serial.begin(115200);

  transmitter.enableTransmit(transmitterPin);

  Serial.println();
  Serial.println("433 mhz transmitter initialized");
  Serial.println("data pin: gpio23");
  Serial.println();
  Serial.println("1 - lamp 1 on");
  Serial.println("2 - lamp 1 off");
  Serial.println("3 - lamp 2 on");
  Serial.println("4 - lamp 2 off");
}

void loop() {
  if (!Serial.available()) {
    return;
  }

  char command = Serial.read();

  switch (command) {
    case '1':
      sendCode(lamp1On, "lamp 1 on");
      break;

    case '2':
      sendCode(lamp1Off, "lamp 1 off");
      break;

    case '3':
      sendCode(lamp2On, "lamp 2 on");
      break;

    case '4':
      sendCode(lamp2Off, "lamp 2 off");
      break;
  }
}
