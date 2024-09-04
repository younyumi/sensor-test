#include <Arduino.h>    // 필수 include
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial gpsSerial(4, 3);  // RX, TX
RF24 radio(9, 10);  // CE, CSN for NRF24L01
TinyGPSPlus gps;

const byte address[6] = "00001";  // 송수신 주소

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);  // GPS 모듈과 통신 시작
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();  // 송신 모드
}

void loop() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());  // GPS 데이터 읽기

    if (gps.location.isUpdated()) {
      float latitude = gps.location.lat();
      float longitude = gps.location.lng();

      // GPS 데이터를 문자열로 포맷
      char gpsData[32];
      //sprintf(gpsData, "Lat:%.6f,Lng:%.6f", latitude, longitude);
      printf("Lat:%.6f,Lng:%.6f", (double)latitude, (double)longitude);


      // 데이터를 전송
      radio.write(&gpsData, sizeof(gpsData));

      // 시리얼 모니터에 출력
      Serial.println(gpsData);
    }
  }
}
