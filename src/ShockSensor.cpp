#include <Arduino.h>

const int sensorPins[4] = {2,3,4,5};
unsigned long DetectedTimes[4] = {0,0,0,0};
const unsigned long debounceTime = 500; //debounce 시간 설정-> 테스트 해보면서 결정해야할듯

void setup(){
  Serial.begin(9600);
  for (int i=0;i<4; i++){
    pinMode(sensorPins[i], INPUT);
  }
}

void loop(){
  for (int i=0; i<4; i++){
    int sensorValue = digitalRead(sensorPins[i]);

    if(sensorValue == LOW){
      unsigned long currentTime = millis();
      if(currentTime -DetectedTimes[i] > debounceTime) { //debounce 시간 지나고 충격감지됐을때 유효한걸로 처리
        float time = currentTime / 1000.0;
        
        Serial.print("Shock detected on sensor");
        Serial.print(i+1);
        Serial.print(" at time: ");
        Serial.print(time, 3);
        Serial.print(" s");
        DetectedTimes[i] = currentTime;
      }
    }
  }
  delay(50);
}

