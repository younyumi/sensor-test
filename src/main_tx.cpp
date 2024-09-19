#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define TRIG_PIN1 2  // 초음파 센서 1
#define ECHO_PIN1 3
#define TRIG_PIN2 4  // 초음파 센서 2
#define ECHO_PIN2 5
#define TRIG_PIN3 6  // 초음파 센서 3
#define ECHO_PIN3 7
#define TRIG_PIN4 8  // 초음파 센서 4
#define ECHO_PIN4 9

#define SHOCK_SENSOR_PIN1 A0  // 좌측 앞바퀴 충격 감지 센서
#define SHOCK_SENSOR_PIN2 A1  // 우측 앞바퀴 충격 감지 센서
#define SHOCK_SENSOR_PIN3 A2  // 좌측 뒷바퀴 충격 감지 센서
#define SHOCK_SENSOR_PIN4 A3  // 우측 뒷바퀴 충격 감지 센서

RF24 radio(10, 11);  // CE, CSN 핀
const byte address[6] = "00001";  // 송수신에 사용할 주소

void setup() {
  Serial.begin(115200);

  // 초음파 센서 핀 설정
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(TRIG_PIN3, OUTPUT);
  pinMode(ECHO_PIN3, INPUT);
  pinMode(TRIG_PIN4, OUTPUT);
  pinMode(ECHO_PIN4, INPUT);
  
  // 충격 감지 센서 핀 설정
  pinMode(SHOCK_SENSOR_PIN1, INPUT);
  pinMode(SHOCK_SENSOR_PIN2, INPUT);
  pinMode(SHOCK_SENSOR_PIN3, INPUT);
  pinMode(SHOCK_SENSOR_PIN4, INPUT);

  if (!radio.begin()) {
    Serial.println("Radio hardware is not responding!");
    while (1);  // 문제 발생 시 멈춤
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
}

long measureDistance(int trigPin, int echoPin) {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // cm로 변환
  return distance;
}

void loop() {
  // 초음파 센서 거리 측정
  long distance1 = measureDistance(TRIG_PIN1, ECHO_PIN1);
  long distance2 = measureDistance(TRIG_PIN2, ECHO_PIN2);
  long distance3 = measureDistance(TRIG_PIN3, ECHO_PIN3);
  long distance4 = measureDistance(TRIG_PIN4, ECHO_PIN4);
  
  // 충격 감지 센서 값 확인
  int shockDetected1 = digitalRead(SHOCK_SENSOR_PIN1);
  int shockDetected2 = digitalRead(SHOCK_SENSOR_PIN2);
  int shockDetected3 = digitalRead(SHOCK_SENSOR_PIN3);
  int shockDetected4 = digitalRead(SHOCK_SENSOR_PIN4);

  // 거리 변화와 충격 감지 여부 분석
  int ultrasonicChangeCount = 0;
  int shockDetectedCount = 0;

  if (distance1 < 100) ultrasonicChangeCount++;
  if (distance2 < 100) ultrasonicChangeCount++;
  if (distance3 < 100) ultrasonicChangeCount++;
  if (distance4 < 100) ultrasonicChangeCount++;

  if (shockDetected1 == HIGH) shockDetectedCount++;
  if (shockDetected2 == HIGH) shockDetectedCount++;
  if (shockDetected3 == HIGH) shockDetectedCount++;
  if (shockDetected4 == HIGH) shockDetectedCount++;

  // 포트홀 탐지
  bool isPothole = (ultrasonicChangeCount > 0 && ultrasonicChangeCount <= 2 && shockDetectedCount > 0 && shockDetectedCount <= 2);

  // 과속방지턱 탐지
  bool isSpeedBump = (ultrasonicChangeCount == 4 && shockDetectedCount == 4);

  if (isPothole && !isSpeedBump) {
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
