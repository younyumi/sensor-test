#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "00001";  // 송수신 주소

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();  // 수신 모드
}

void loop() {
  if (radio.available()) {
    char gpsData[32] = "";
    radio.read(&gpsData, sizeof(gpsData));  // 데이터 수신

    // 수신된 데이터를 시리얼 모니터에 출력
    Serial.print("Received GPS Data: ");
    Serial.println(gpsData);
  }
}
