int currentState;
int currentSeq;

int correctSeq = 4451;

int lastPress;

int MOTOR_PIN = 11;
int RED_LED = 12;
int GREEN_LED = 13;

int BUTTON[] = { 2, 3, 4, 5, 6 };
int buttonVal[] = { 0, 0, 0, 0, 0 };

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(BUTTON[i], INPUT);
  }
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  currentState = 0;
  currentSeq = 0;
  lastPress = 0;
}

void loop() {
  // read all inputs
  for (int i = 0; i < 5; i++) {
    buttonVal[i] = digitalRead(BUTTON[i]);
  }

  if (buttonVal[0] == HIGH) {
    currentSeq = currentSeq * 10 + 1;
    currentState += 1;
    lastPress = millis();
  } else if (buttonVal[1] == HIGH) {
    currentSeq = currentSeq * 10 + 2;
    currentState += 1;
    lastPress = millis();
  } else if (buttonVal[2] == HIGH) {
    currentSeq = currentSeq * 10 + 3;
    currentState += 1;
    lastPress = millis();
  } else if (buttonVal[3] == HIGH) {
    currentSeq = currentSeq * 10 + 4;
    currentState += 1;
    lastPress = millis();
  } else if (buttonVal[4] == HIGH) {
    currentSeq = currentSeq * 10 + 5;
    currentState += 1;
    lastPress = millis();
  }

  // check timer
  if (millis() - lastPress > 5000) {
    currentState = 0;
    currentSeq = 0;
    lastPress = millis();
    digitalWrite(RED_LED, HIGH);
  }

  // check sequence if 4 buttons have been pressed
  if (currentState == 4) {
    if (currentSeq == correctSeq) {
      digitalWrite(MOTOR_PIN, HIGH);
      digitalWrite(GREEN_LED, HIGH);
    } else {
      digitalWrite(RED_LED, HIGH);
    }
    currentState = 0;
    currentSeq = 0;
    lastPress = millis();
  }

  delay(50);
}
