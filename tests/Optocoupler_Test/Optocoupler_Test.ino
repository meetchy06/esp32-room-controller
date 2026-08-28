const int remoteOn = 16;
const int remoteOff = 17;
const int brightnessUp = 18;
const int brightnessDown = 19;

void pulseButton(int pin) {
  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(remoteOn, OUTPUT);
  pinMode(remoteOff, OUTPUT);
  pinMode(brightnessUp, OUTPUT);
  pinMode(brightnessDown, OUTPUT);

  digitalWrite(remoteOn, LOW);
  digitalWrite(remoteOff, LOW);
  digitalWrite(brightnessUp, LOW);
  digitalWrite(brightnessDown, LOW);

  Serial.println("o on");
  Serial.println("f off");
  Serial.println("u brightness up");
  Serial.println("d brightness down");
}

void loop() {
  if (!Serial.available()) {
    return;
  }

  char command = Serial.read();

  switch (command) {
    case 'o':
      pulseButton(remoteOn);
      break;

    case 'f':
      pulseButton(remoteOff);
      break;

    case 'u':
      pulseButton(brightnessUp);
      break;

    case 'd':
      pulseButton(brightnessDown);
      break;
  }
}
