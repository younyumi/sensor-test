#include <Arduino.h>

const int sensorPin = 2; // Using pin 2 for the SW-420 sensor
unsigned long lastDetectedTime = 0;
const unsigned long debounceTime = 500; // Debounce time in milliseconds

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int sensorValue = digitalRead(sensorPin);

  if (sensorValue == HIGH) { // LOW indicates shock detected
    unsigned long currentTime = millis();
    if (currentTime - lastDetectedTime > debounceTime) { // Check if debounce time has passed
      float time = currentTime / 1000.0;

      Serial.print("Shock detected at time: ");
      Serial.print(time, 3);
      Serial.println(" s");
      lastDetectedTime = currentTime;
    }
  }
  delay(100); // Small delay to reduce CPU usage
}
