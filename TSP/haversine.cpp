// ---------------- haversine.cpp ----------------
#include "haversine.h"
#include <cmath>

const double R = 6371.0; // Earth radius in km

double deg2rad(double deg) {
    return deg * M_PI / 180.0;
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
    lat1 = deg2rad(lat1);
    lon1 = deg2rad(lon1);
    lat2 = deg2rad(lat2);
    lon2 = deg2rad(lon2);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    double a = std::pow(std::sin(dlat / 2), 2) + std::cos(lat1) * std::cos(lat2) * std::pow(std::sin(dlon / 2), 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return R * c;
}
