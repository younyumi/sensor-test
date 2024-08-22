#ifndef GPS_H
#define GPS_H

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

class GPSModule {
public:
    GPSModule(int rxPin, int txPin, long baudRate = 9600);
    void begin();
    void update();
    double getLatitude();
    double getLongitude();
    bool locationIsValid();

private:
    TinyGPSPlus gps;
    SoftwareSerial ss;
    double latitude;
    double longitude;
    bool locationValid;
};

#endif // GPS_H
