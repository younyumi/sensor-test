#ifndef TINYGPSPLUS_H
#define TINYGPSPLUS_H

class TinyGPSLocation {
public:
    TinyGPSLocation();

    double lat() const;
    double lng() const;

    bool isUpdated() const;
    void setLocation(double lat, double lng);

private:
    double _lat;
    double _lng;
};
class TinyGPSPlus {
public:
    TinyGPSPlus();

    void encode(char c);
    TinyGPSLocation location;

private:
};

#endif // TINYGPSPLUS_H