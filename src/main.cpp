

// #include <DFRobotDFPlayerMini.h>

// DFRobotDFPlayerMini myMP3;  //18.19

// void setup() {
//   Serial.begin(115200); // 디버깅을 위한 기본 Serial
//   Serial1.begin(9600);  // MP3 모듈과의 통신을 위한 Serial1

//   if (!myMP3.begin(Serial1)) {  // DFPlayer 초기화
//     Serial.println("fail");
//     while (true);
//   }

//   Serial.println("..");
//   myMP3.volume(20);  // 볼륨 설정 (0~30)
//   myMP3.play(1);     // 첫 번째 트랙 재생
// }

// void loop() {
//   // 추가 로직이 필요 없다면 빈 상태로 유지
// }



















// #include <DFRobotDFPlayerMini.h>

// DFRobotDFPlayerMini myMP3;

// void setup() {
//   Serial.begin(115200); // 디버깅을 위한 기본 Serial
//   Serial1.begin(9600);  // MP3 모듈과의 통신을 위한 Serial1

//   if (!myMP3.begin(Serial1)) {  // DFPlayer 초기화
//     Serial.println("DFPlayer Mini 초기화 실패!");
//     while (true);
//   }

//   Serial.println("DFPlayer Mini 준비 완료.");
//   myMP3.volume(20);  // 볼륨 설정 (0~30)
//   myMP3.loop(1);     // 첫 번째 트랙을 무한 반복 재생
// }

// void loop() {

// }





//스로틀
// #include <DFRobotDFPlayerMini.h>

// DFRobotDFPlayerMini myMP3;
// int throttlePin = A0;  // 스로틀이 연결된 아날로그 핀
// int threshold = 300;   // 스로틀 값이 이 값을 초과할 때 소리 재생

// void setup() {
//   Serial.begin(115200);  // 디버깅을 위한 기본 Serial
//   Serial1.begin(9600);   // MP3 모듈과의 통신을 위한 Serial1

//   if (!myMP3.begin(Serial1)) {  // DFPlayer 초기화
//     Serial.println("DFPlayer Mini 초기화 실패!");
//     while (true);
//   }

//   Serial.println("DFPlayer Mini 준비 완료.");
//   myMP3.volume(20);  // 볼륨 설정 (0~30)
// }

// void loop() {
//   int throttleValue = analogRead(throttlePin);  // 스로틀 값 읽기

//   if (throttleValue > threshold) {
//     Serial.println("playing...");
//     myMP3.play(1);  // 첫 번째 트랙 재생
//   } else {
//     myMP3.stop();   // 소리 정지
//     Serial.println("none throttle.");
//   }

//   delay(100);  // 반복 주기 (지연 시간 설정)
// }








//볼륨조절

// #include <DFRobotDFPlayerMini.h>

// DFRobotDFPlayerMini myMP3;
// int volumeLevel = 5;       
// unsigned long prevMillis = 0;
// unsigned long interval = 500;  

// void setup() {
//   Serial.begin(115200); 
//   Serial1.begin(9600);  

//   if (!myMP3.begin(Serial1)) {  // DFPlayer 초기화
//     Serial.println("fail!");
//     while (true);
//   }

//   Serial.println("ready.");
//   myMP3.volume(volumeLevel); 
//   myMP3.loop(1); 
// }            

// void loop() {
//   unsigned long currentMillis = millis();

//   if (currentMillis - prevMillis >= interval) {
//     prevMillis = currentMillis; 

//     if (volumeLevel < 30) {  
//       volumeLevel++;
//       myMP3.volume(volumeLevel);  
//       Serial.print("현재 볼륨: ");
//       Serial.println(volumeLevel);
//     }
//   }
// }


#include <DFRobotDFPlayerMini.h>

DFRobotDFPlayerMini myMP3;

int soundSensorPin = A0;  // 소리 감지 센서 핀
int threshold = 300;      // 소리 감지 임계값
bool isPlaying = false;   // 현재 재생 상태를 저장

void setup() {
  Serial.begin(115200); // 디버깅을 위한 기본 Serial
  Serial1.begin(9600);  // MP3 모듈과의 통신을 위한 Serial1

  if (!myMP3.begin(Serial1)) {  // DFPlayer 초기화
    Serial.println("fail!");
    while (true);
  }

  Serial.println("ready.");
  myMP3.volume(30);  // 볼륨 설정 (0~30)
}

void loop() {
  int soundLevel = analogRead(soundSensorPin);  // 소리 감지 센서 값 읽기
  Serial.println(soundLevel); 

  if (soundLevel > threshold) {
    if (!isPlaying) {  
      myMP3.loop(1);   
      isPlaying = true;
      Serial.println("MP3 재생 시작");
    }
  } else {
    if (isPlaying) {  
      myMP3.stop();   
      isPlaying = false;
      Serial.println("MP3 재생 중지");
    }
  }

  delay(100);  // 감지 주기 설정
}



// #include <DFRobotDFPlayerMini.h>

// DFRobotDFPlayerMini myMP3;

// int soundSensorPin = A0;  // 소리 감지 센서 핀
// int lowerThreshold = 300; // 하한 임계값
// int upperThreshold = 700; // 상한 임계값
// bool isPlaying = false;   // 현재 재생 상태를 저장

// void setup() {
//   Serial.begin(115200); // 디버깅을 위한 기본 Serial
//   Serial1.begin(9600);  // MP3 모듈과의 통신을 위한 Serial1

//   if (!myMP3.begin(Serial1)) {  // DFPlayer 초기화
//     Serial.println("DFPlayer Mini 초기화 실패!");
//     while (true);
//   }

//   Serial.println("DFPlayer Mini 준비 완료.");
//   myMP3.volume(20);  // 볼륨 설정 (0~30)
// }

// void loop() {
//   int soundLevel = analogRead(soundSensorPin);  // 소리 감지 센서 값 읽기
//   Serial.println(soundLevel);  // 소리 감지 값 출력 (디버깅 용도)

//   // 소리 감지 값이 하한과 상한 임계값 사이일 때만
//   if (soundLevel > lowerThreshold && soundLevel < upperThreshold) {
//     if (!isPlaying) {  // 현재 재생 중이 아니면
//       myMP3.loop(1);   // 첫 번째 트랙 재생
//       isPlaying = true;
//       Serial.println("MP3 재생 시작");
//     }
//   } else {
//     if (isPlaying) {  // 현재 재생 중이면
//       myMP3.stop();   // 재생 중지
//       isPlaying = false;
//       Serial.println("MP3 재생 중지");
//     }
//   }

//   delay(100);  // 감지 주기 설정
// }

