#include "TinyGPS++.h"
#include <stdlib.h>
#include <string.h>

TinyGPSPlus::TinyGPSPlus() {}

void TinyGPSPlus::encode(char c) {
    static bool isParsing = false;
    static char nmeaSentence[100];
    static int index = 0;

    if (c == '$') {
        isParsing = true;
        index = 0;
    }

    if (isParsing) {
        nmeaSentence[index++] = c;
        if (c == '\n') {
            nmeaSentence[index] = '\0';
            isParsing = false;

            // GPGGA 메시지를 파싱하여 위치 데이터를 추출
            if (strstr(nmeaSentence, "GPGGA")) {
                char* tokens[15];
                int tokenIndex = 0;
                char* str = strtok(nmeaSentence, ",");

                while (str != nullptr && tokenIndex < 15) {
                    tokens[tokenIndex++] = str;
                    str = strtok(nullptr, ",");
                }

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

                    // 위치 데이터를 설정
                    location.setLocation(latitude, longitude);
                }
            }
        }
    }
}

TinyGPSLocation::TinyGPSLocation() : _lat(0.0), _lng(0.0) {}

double TinyGPSLocation::lat() const {
    return _lat;
}

double TinyGPSLocation::lng() const {
    return _lng;
}

void TinyGPSLocation::setLocation(double lat, double lng) {
    _lat = lat;
    _lng = lng;
}

bool TinyGPSLocation::isUpdated() const {
    // 위치 데이터가 업데이트된 경우 true를 반환하는 로직을 여기에 추가
    // 이 예제에서는 간단히 항상 true를 반환하도록 합니다.
    return true;
}
