void setup() {
  Serial.begin(9600);
  while (!Serial) {}
}

void loop() {
  int a0Val = analogRead(A0);

  if (Serial.available() > 0) {
    int byteIn = Serial.read();
    if (byteIn == 0xAB) {
      Serial.flush();
      Serial.println(a0Val);
    }
  }

  delay(2);
}
