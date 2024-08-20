#include <Arduino.h>
#include "Ultrasonic.h"

UltrasonicSensor sensor(10, 8); // 초음파 센서 핀 설정

void setup() {
    Serial.begin(115200);
}

void loop() {
    int distance = sensor.getDistance();
    Serial.println("Distance: " + String(distance) + " cm");
    delay(1000);
}
