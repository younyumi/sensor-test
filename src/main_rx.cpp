#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

RF24 radio(9, 10);  // CE, CSN 핀
const byte address[6] = "00001";  // 송수신에 사용할 주소

// I2C 주소와 LCD 크기 설정 (예: 16x2 LCD 사용)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  
  // LCD 초기화
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for data");

  // RF24 초기화
  radio.begin();
  radio.openReadingPipe(0, address);  // 수신 파이프 설정
  radio.setPALevel(RF24_PA_LOW);      // 전송 전력 설정
  radio.startListening();             // 수신 모드 전환
}

void loop() {
  if (radio.available()) {
  char text[32] = {0};
  radio.read(&text, sizeof(text));
  
  if (strcmp(text, "pothole detected") == 0) {
    lcd.setCursor(0, 0);  // 커서를 이동하여 기존 글씨 덮어쓰기
    lcd.print("Pothole Detected");
  }
}

}
