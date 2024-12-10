// Using: ArduinoJson by Benoit Blanchon
// v6.21.5
#include <ArduinoJson.h>

void sendData(int val, int vMin, int vMax) {
  StaticJsonDocument<128> resJson;
  JsonObject data = resJson.createNestedObject("data");
  JsonObject A0 = data.createNestedObject("A0");

  A0["value"] = val;
  A0["min"] = vMin;
  A0["max"] = vMax;

  String resTxt = "";
  serializeJson(resJson, resTxt);

  Serial.println(resTxt);
}

int a0Min;
int a0Max;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  a0Min = 4095;
  a0Max = 0;
}

void loop() {
  int a0Val = analogRead(A0);
  a0Min = min(a0Min, a0Val);
  a0Max = max(a0Max, a0Val);

  if (Serial.available() > 0) {
    int byteIn = Serial.read();
    if (byteIn == 0xAB) {
      Serial.flush();
      sendData(a0Val, a0Min, a0Max);
    }
  }

  delay(2);
}