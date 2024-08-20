#include <Arduino.h>
#include "GPS.h"

GPSModule gpsModule(Serial);

void setup() {
    Serial.begin(9600);
    gpsModule.begin();
}

void loop() {
    gpsModule.update();
    if (gpsModule.locationIsValid()) {
        Serial.print("Latitude: ");
        Serial.print(gpsModule.getLatitude(), 6);
        Serial.print(" Longitude: ");
        Serial.print(gpsModule.getLongitude(), 6);
        Serial.print(" Altitude: ");
        Serial.print(gpsModule.getAltitude());
        Serial.println(" meters");
    } else {
        Serial.println("Location not valid.");
    }
    delay(1000);
}
