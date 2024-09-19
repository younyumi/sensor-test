#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define TRIG_PIN 7  // 초음파 센서 Trig 핀
#define ECHO_PIN 6  // 초음파 센서 Echo 핀
#define SHOCK_SENSOR_PIN 8  // 충격 감지 센서 핀

RF24 radio(9, 10);  // CE, CSN 핀
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(SHOCK_SENSOR_PIN, INPUT);
  
  if (!radio.begin()) {
    Serial.println("Radio hardware is not responding!");
    while (1);  // 문제가 있을 경우 멈춤
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
}

void loop() {
  // 초음파 센서로 거리 측정
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;  // cm로 변환

  // 충격 감지 센서로 충격 확인
  int shockDetected = digitalRead(SHOCK_SENSOR_PIN);

  // 거리 변화가 5cm 이상이거나 충격이 감지된 경우
  if ((distance < 100 && distance > 5) || shockDetected == HIGH) {
    const char text[] = "Warning! Pothole";
    bool success = radio.write(&text, sizeof(text));
    
    if (success) {
      Serial.println("Pothole detected, message sent");
    } else {
      Serial.println("Failed to send");
    }
  }
  delay(1000);
}
