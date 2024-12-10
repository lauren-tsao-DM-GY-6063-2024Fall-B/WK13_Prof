// Using: ArduinoJson by Benoit Blanchon
// v6.21.5
#include <ArduinoJson.h>

void receiveData(const char* jsonText) {
  StaticJsonDocument<128> resJson;
  DeserializationError error = deserializeJson(resJson, jsonText);

  if (error) {
    Serial.println(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  int x = resJson["data"]["x"];
  int y = resJson["data"]["y"];
  int w = resJson["data"]["w"];
  int h = resJson["data"]["h"];

  int xVal = map(x, 0, w, 0, 255);
  int yVal = map(y, 0, h, 0, 255);

  analogWrite(2, xVal);
  analogWrite(3, yVal);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  analogWrite(2, 0);
  analogWrite(3, 0);
}

void loop() {
  if (Serial.available() > 0) {
    String jsonText = Serial.readStringUntil('\n');
    receiveData(jsonText.c_str());
  }

  delay(2);
}
