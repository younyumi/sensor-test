#include "GPS.h"

GPSModule::GPSModule(int rxPin, int txPin, long baudRate)
    : ss(rxPin, txPin), latitude(0.0), longitude(0.0), locationValid(false) {
    ss.begin(baudRate);
}

void GPSModule::begin() {
    ss.begin(115200); 
}

void GPSModule::update() {
    while (ss.available() > 0) {
        if (gps.encode(ss.read())) {
            if (gps.location.isUpdated()) {
                latitude = gps.location.lat();
                longitude = gps.location.lng();
                locationValid = true;
            }
        }
    }
}

double GPSModule::getLatitude() {
    return latitude;
}

double GPSModule::getLongitude() {
    return longitude;
}

bool GPSModule::locationIsValid() {
    return locationValid;
}
