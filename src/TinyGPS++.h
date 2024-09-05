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
    // 필요한 멤버 변수 및 메서드를 여기에 추가할 수 있습니다.
};

#endif // TINYGPSPLUS_H