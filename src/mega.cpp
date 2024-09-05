#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN 핀 설정

const byte address[6] = "00001"; // 송신/수신 주소 설정

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address); // 송신 파이프 열기
  radio.setPALevel(RF24_PA_MIN); // 전송 파워 설정
  radio.stopListening(); // 송신 모드로 설정
}

void loop() {
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text)); // 데이터 전송
  Serial.println("Sent: Hello World");
  delay(1000);
}
