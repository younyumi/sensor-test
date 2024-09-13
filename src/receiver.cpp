#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN

const byte address[6] = "00001";  // 송신자와 동일한 주소 사용

void setup() {
  Serial.begin(9600);
  
  if (!radio.begin()) {
    Serial.println("Radio hardware is not responding!");
    while (1);
  }

  radio.openReadingPipe(0, address);  // 수신용 파이프 설정
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();  // 수신 모드 시작
}

void loop() {
  if (radio.available()) {  // 데이터가 수신 가능할 때
    char text[32] = "";  // 수신할 데이터를 담을 배열
    radio.read(&text, sizeof(text));  // 데이터 수신
    Serial.println(text);  // 수신한 데이터 출력
  }
}
