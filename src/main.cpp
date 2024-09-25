// #include <Arduino.h>
// #include "TinyGPS++.h"
// #include "MultiUltrasonic.h"
// #include "MPU6050.h"  
// #include "shocksensor.h"

// static const uint32_t GPSBaud = 9600;  // GPS 모듈의 통신 속도

// const int num = 2;  // 두 개의 MPU6050 센서

// int trig[4] = {2, 4, 6, 8};
// int echo[4] = {3, 5, 7, 9};

// // 두 개의 MPU6050의 I2C 주소 (0x68, 0x69)  68이 GND, 69가 3.3V
// int mpuAddresses[num] = {0x69, 0x68};
// int shockPins[4] = {40, 41, 42, 43};

// const char* sensorLabels[4] = {"FR", "FL", "RR", "RL"};

// TinyGPSPlus gps;
// MultiUltrasonic ultrasonicSensors(trig, echo, 4);
// MPU6050* mpu6050Sensors[num];  // 두 개의 MPU6050 센서
// ShockSensor* shockSensors[4];

// void setup() {
//     // 시리얼 통신 초기화
//     Serial.begin(115200); // 컴퓨터와의 통신 속도
//     Serial1.begin(GPSBaud);  // GPS 모듈과의 통신 속도
//     ultrasonicSensors.begin();  // 초음파 센서 초기화

//     // MPU6050 센서 초기화
//     for (int i = 0; i < num; i++) {
//         mpu6050Sensors[i] = new MPU6050(mpuAddresses[i]);
//         mpu6050Sensors[i]->initialize();
//     }

//     // 충격 센서 초기화
//     for (int i = 0; i < 4; i++) {
//         shockSensors[i] = new ShockSensor(shockPins[i]);
//     }
// }
// void loop() {
//     // 초음파 거리 업데이트
//     ultrasonicSensors.update();

//     // 각 초음파 센서의 거리 출력
//     for (int i = 0; i < 4; i++) {
//         Serial.print("Ultrasonic ");
//         Serial.print(i + 1);
//         Serial.print(": ");
//         Serial.println(ultrasonicSensors.getDistance(i));
//     }

//     // 각 충격 센서의 감지 상태 출력
//     for (int i = 0; i < 4; i++) {
//         Serial.print("Shock Sensor ");
//         Serial.print(sensorLabels[i]);
//         Serial.print(": ");
//         Serial.println(shockSensors[i]->isShockDetected() ? "1" : "0");
//     }

//     // 두 개의 MPU6050 센서의 가속도와 Roll, Pitch 출력
//     for (int i = 0; i < num; i++) {
//         float ax = mpu6050Sensors[i]->getAccelerationX();
//         float ay = mpu6050Sensors[i]->getAccelerationY();
//         float az = mpu6050Sensors[i]->getAccelerationZ();
//         float roll = mpu6050Sensors[i]->calculateRoll(ax, ay, az);
//         float pitch = mpu6050Sensors[i]->calculatePitch(ax, ay, az);

//         Serial.print("MPU6050 Sensor ");
//         Serial.print(i + 1);
//         Serial.print(" Z_acc : ");
//         Serial.println(az);
//         Serial.print("Roll: ");
//         Serial.println(roll);
//         Serial.print("Pitch: ");
//         Serial.println(pitch);
//     }

//     // GPS 데이터 처리
//     static String ggaMessage = "";
    
//     while (Serial1.available() > 0) {
//         char c = Serial1.read();

//         if (c == '\n') {
//             // GPGGA 메시지를 찾고, 파싱을 시작합니다.
//             if (ggaMessage.startsWith("$GPGGA")) {
//                 // 위도와 경도를 추출합니다.
//                 char* tokens[15]; // GGA 메시지를 ','를 기준으로 나누기 위한 배열
//                 int tokenIndex = 0;
//                 char* str = strtok(&ggaMessage[0], ",");

//                 while (str != nullptr && tokenIndex < 15) {
//                     tokens[tokenIndex++] = str;
//                     str = strtok(nullptr, ",");
//                 }

//                 // 위도와 경도를 변환하여 출력합니다.
//                 if (tokenIndex >= 6) {
//                     // 위도 변환
//                     float rawLatitude = atof(tokens[2]);
//                     int latDegrees = (int)(rawLatitude / 100);
//                     float latMinutes = rawLatitude - (latDegrees * 100);
//                     float latitude = latDegrees + (latMinutes / 60.0);

//                     // 경도 변환
//                     float rawLongitude = atof(tokens[4]);
//                     int lonDegrees = (int)(rawLongitude / 100);
//                     float lonMinutes = rawLongitude - (lonDegrees * 100);
//                     float longitude = lonDegrees + (lonMinutes / 60.0);

//                     // 변환된 위도와 경도를 출력합니다.
//                     Serial.print("Latitude: ");
//                     Serial.print(latitude, 6);
//                     Serial.print(", Longitude: ");
//                     Serial.println(longitude, 6);
//                 }
//             }

//             ggaMessage = ""; 
//         } else {
//             ggaMessage += c;
//         }
//     }

//     Serial.println("---------------------");

//     delay(1000);
// } 



#include <Arduino.h>
#include "TinyGPS++.h"
#include "MultiUltrasonic.h"

static const uint32_t GPSBaud = 9600;  // GPS module baud rate

int trig[4] = {2, 4, 6, 8};
int echo[4] = {3, 5, 7, 9};

TinyGPSPlus gps;
MultiUltrasonic ultrasonicSensors(trig, echo, 4);

void setup() {
    // Initialize serial communication
    Serial.begin(115200);  // Communication with PC
    Serial1.begin(GPSBaud);  // Communication with GPS module
    ultrasonicSensors.begin();  // Initialize ultrasonic sensors
}

void loop() {
    // Update the distances from ultrasonic sensors
    ultrasonicSensors.update();

    // Print the distance from each ultrasonic sensor
    for (int i = 0; i < 4; i++) {
        Serial.print("Ultrasonic ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.println(ultrasonicSensors.getDistance(i));
    }

    // Process GPS data
    static String ggaMessage = "";

    while (Serial1.available() > 0) {
        char c = Serial1.read();

        if (c == '\n') {
            // Find GPGGA message and parse it
            if (ggaMessage.startsWith("$GPGGA")) {
                // Split GGA message by commas
                char* tokens[15];
                int tokenIndex = 0;
                char* str = strtok(&ggaMessage[0], ",");

                while (str != nullptr && tokenIndex < 15) {
                    tokens[tokenIndex++] = str;
                    str = strtok(nullptr, ",");
                }

                // Convert latitude and longitude and print
                if (tokenIndex >= 6) {
                    // Convert latitude
                    float rawLatitude = atof(tokens[2]);
                    int latDegrees = (int)(rawLatitude / 100);
                    float latMinutes = rawLatitude - (latDegrees * 100);
                    float latitude = latDegrees + (latMinutes / 60.0);

                    // Convert longitude
                    float rawLongitude = atof(tokens[4]);
                    int lonDegrees = (int)(rawLongitude / 100);
                    float lonMinutes = rawLongitude - (lonDegrees * 100);
                    float longitude = lonDegrees + (lonMinutes / 60.0);

                    // Output latitude and longitude
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

    Serial.println("---------------------");

    delay(1000);
}
