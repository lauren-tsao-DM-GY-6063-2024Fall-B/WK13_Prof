// Using: ArduinoJson by Benoit Blanchon
// v6.21.5
#include <ArduinoJson.h>

void receiveData(const char* jsonText) { // how to turn something written in text (string) and convert them into numbers
  StaticJsonDocument<128> resJson; // this line and the one below reads diff in the json plugin version 7 from benoit
  DeserializationError error = deserializeJson(resJson, jsonText); // turns text into an object

  if (error) { // if cannot convert string into numbers
    Serial.println(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

// resJson is a custom variable, it can be also called mData etc.
  int x = resJson["data"]["x"]; // if converting text into numbers was successful, this block of code is executed
  int y = resJson["data"]["y"]; // this formula works the same way in as this javascript code : e.g y.data, y.y (you can use this c++ format int javascript but not the other way around)
  int w = resJson["data"]["w"]; // access data first, and then x
  int h = resJson["data"]["h"]; // this format is called dictionaries or hashes or hash maps/tables (although its called objects in p5js)

  int xVal = map(x, 0, w, 0, 255);
  int yVal = map(y, 0, h, 0, 255);

  analogWrite(2, xVal);
  analogWrite(3, yVal);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {} // stops the code and wait for the serial port to open (i.e. wait till the serial is ready)

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
