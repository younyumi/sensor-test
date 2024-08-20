#include <Arduino.h>
#include "UltrasonicSensor.h"

UltrasonicSensor sensor(2, 3); // 초음파 센서 핀 설정

void setup() {
    Serial.begin(115200);
}

void loop() {
    int distance = sensor.getDistance();
    Serial.println("Distance: " + String(distance) + " cm");
    delay(1000);
}
