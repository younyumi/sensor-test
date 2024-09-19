#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

RF24 radio(9, 10);  // CE, CSN 핀
const byte address[6] = "00001";  // 송수신에 사용할 주소

// I2C 주소와 LCD 크기 설정 (예: 16x2 LCD 사용)
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long previousMillis = 0;  
const long displayDuration = 1500;  //디스플레이에 경고 나타내는 시간 

bool displayMessage = false; 
unsigned long messageStartTime = 0;  

void setup() {
  Serial.begin(115200);
  
  // LCD 초기화
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for data");

  // RF24 초기화
  radio.begin();
  radio.openReadingPipe(0, address);  
  radio.setPALevel(RF24_PA_LOW);      
  radio.startListening();             
}

void loop() {
  unsigned long currentMillis = millis();  // 현재 시간 추적

  // 메시지가 수신될 경우
  if (radio.available()) {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    
    if (strcmp(text, "Warning! Pothole") == 0) {
      lcd.setCursor(0, 0);  // 커서를 이동하여 기존 글씨 덮어쓰기
      lcd.print("Warning! Pothole");

      displayMessage = true;  // 메시지 표시 시작
      messageStartTime = currentMillis;  // 메시지 표시 시작 시간 기록
    }
  }

  // 메시지 표시한 후 지우기
  if (displayMessage && (currentMillis - messageStartTime >= displayDuration)) {
    lcd.clear();
    displayMessage = false;  // 메시지 표시 종료
  }
}
