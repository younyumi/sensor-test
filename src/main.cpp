#include <Arduino.h>
#include "ShockSensor.h"

ShockSensor shockSensor(2);  // 센서 연결 핀번호

unsigned long previousMillis = 0;  //시간 변수
const long interval = 100;         // 100밀리초마다 충격 감지

void setup() {
  
  Serial.begin(9600);

  shockSensor.begin();

  // 초기 메시지 출력
  Serial.println("Starting Pothole Detection...");
}

void loop() {
  // 현재 시간 읽기
  unsigned long currentMillis = millis();

  // 주기적으로 충격 감지 확인
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // 이전 시간을 현재 시간으로 업데이트

    // 충격 감지 시 시리얼 모니터에 데이터 출력
    if (shockSensor.isShockDetected()) {
      Serial.print("Shock detected at: ");
      Serial.print(currentMillis);
      Serial.println(" ms");
    }
  }
}
