#include <RCSwitch.h>

RCSwitch receiver;

const int receiverPin = 26;

void setup() {
  Serial.begin(115200);

  receiver.enableReceive(digitalPinToInterrupt(receiverPin));

  Serial.println("433 mhz receiver ready");
}

void loop() {
  if (!receiver.available()) {
    return;
  }

  Serial.println("----------------");

  Serial.print("value: ");
  Serial.println(receiver.getReceivedValue());

  Serial.print("bits: ");
  Serial.println(receiver.getReceivedBitlength());

  Serial.print("protocol: ");
  Serial.println(receiver.getReceivedProtocol());

  Serial.print("pulse: ");
  Serial.print(receiver.getReceivedDelay());
  Serial.println(" us");

  receiver.resetAvailable();
}
