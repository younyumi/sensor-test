#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN 핀 설정

const byte address[6] = "00001"; // 송신/수신 주소 설정

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address); // 수신 파이프 열기
  radio.setPALevel(RF24_PA_MIN); // 전송 파워 설정
  radio.startListening(); // 수신 모드로 설정
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text)); // 데이터 수신
    Serial.print("Received: ");
    Serial.println(text);
  }
}
