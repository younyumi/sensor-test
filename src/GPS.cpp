#include "GPS.h"

GPSModule::GPSModule(HardwareSerial& serial) : _serial(serial), _latitude(0.0), _longitude(0.0), _altitude(0.0), _locationValid(false) {}

void GPSModule::begin() {
    _serial.begin(9600);
}

void GPSModule::update() {
    while (_serial.available() > 0) {
        if (_gps.encode(_serial.read())) {
            if (_gps.location.isUpdated()) {
                _latitude = _gps.location.lat();
                _longitude = _gps.location.lng();
                _altitude = _gps.altitude.meters();
                _locationValid = true;
            }
        }
    }
}

double GPSModule::getLatitude() {
    return _latitude;
}

double GPSModule::getLongitude() {
    return _longitude;
}

double GPSModule::getAltitude() {
    return _altitude;
}

bool GPSModule::locationIsValid() {
    return _locationValid;
}
