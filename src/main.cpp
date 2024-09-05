#include <Arduino.h>
#include "TinyGPS++.h"

static const uint32_t GPSBaud = 9600; // GPS 모듈의 통신 속도

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600); // 시리얼 모니터와의 통신 시작
  Serial1.begin(GPSBaud); // GPS 모듈과의 통신 시작
}

void loop() {
  // GPS 데이터가 도착할 때까지 기다림
  static String ggaMessage = "";
  
  while (Serial1.available() > 0) {
    char c = Serial1.read();

    if (c == '\n') {
      // GPGGA 메시지를 찾고, 파싱을 시작합니다.
      if (ggaMessage.startsWith("$GPGGA")) {
        // 위도와 경도를 추출합니다.
        char* tokens[15]; // GGA 메시지를 ','를 기준으로 나누기 위한 배열
        int tokenIndex = 0;
        char* str = strtok(&ggaMessage[0], ",");

        while (str != nullptr && tokenIndex < 15) {
          tokens[tokenIndex++] = str;
          str = strtok(nullptr, ",");
        }

        // 위도와 경도를 변환하여 출력합니다.
        if (tokenIndex >= 6) {
          // 위도 변환
          float rawLatitude = atof(tokens[2]);
          int latDegrees = (int)(rawLatitude / 100);
          float latMinutes = rawLatitude - (latDegrees * 100);
          float latitude = latDegrees + (latMinutes / 60.0);

          // 경도 변환
          float rawLongitude = atof(tokens[4]);
          int lonDegrees = (int)(rawLongitude / 100);
          float lonMinutes = rawLongitude - (lonDegrees * 100);
          float longitude = lonDegrees + (lonMinutes / 60.0);

          // 변환된 위도와 경도를 출력합니다.
          Serial.print("Latitude: ");
          Serial.print(latitude, 6);
          Serial.print(", Longitude: ");
          Serial.println(longitude, 6);
        }
      }

      ggaMessage = ""; 
    } else {
      ggaMessage += c;
    }
  }
}