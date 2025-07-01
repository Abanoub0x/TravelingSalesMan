// ---------------- city.h ----------------
#ifndef CITY_H
#define CITY_H

#include <QString>

class City {
public:
    QString name;
    double latitude;
    double longitude;

    City(const QString& name, double lat, double lon)
        : name(name), latitude(lat), longitude(lon) {}
};

#endif // CITY_H
