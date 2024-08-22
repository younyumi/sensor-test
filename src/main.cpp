#include <Arduino.h>
#include "GPS.h"

GPSModule gpsModule(4, 3); // RX, TX 핀 번호

void setup() {
    Serial.begin(115200);
    gpsModule.begin();
}

void loop() {
    gpsModule.update();
    if (gpsModule.locationIsValid()) {
        Serial.print("Latitude: ");
        Serial.println(gpsModule.getLatitude(), 6);
        Serial.print("Longitude: ");
        Serial.println(gpsModule.getLongitude(), 6);
    } else {
        Serial.println("Location not valid.");
    }
    delay(1000);
}
