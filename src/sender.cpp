#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  if (!radio.begin()) {
    Serial.println("Radio hardware is not responding!");
    while (1);  // 문제가 있을 경우 멈춤
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  const char text[] = "Test";
  bool success = radio.write(&text, sizeof(text));

  if (success) {
    Serial.println("Data sent");
  } else {
    Serial.println("Failed to send");
  }

  delay(1000);
}
