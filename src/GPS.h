#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>
#include <HardwareSerial.h>

class GPSModule {
public:
    GPSModule(HardwareSerial& serial);
    void begin();
    void update();
    double getLatitude();
    double getLongitude();
    double getAltitude();
    bool locationIsValid();

private:
    HardwareSerial& _serial;
    TinyGPSPlus _gps;
    double _latitude;
    double _longitude;
    double _altitude;
    bool _locationValid;
};

#endif // GPSMODULE_H
