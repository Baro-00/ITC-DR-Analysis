// GPSData.cpp
#include "GPSData.hpp"
#include <cmath>

// Earth radius in meters
const double EARTH_RADIUS = 6371000.0;
// Convert degrees to radians
inline double deg2rad(double deg) { return deg * M_PI / 180.0; }
// Convert radians to degrees
inline double rad2deg(double rad) { return rad * 180.0 / M_PI; }

GPSData::GPSData()
    : latitude(0.0)
    , longitude(0.0)
    , altitude(0.0)
    , accuracy(0.0)
    , fixType(FixType::NO_FIX)
    , satelliteCount(0)
{
}

GPSData::GPSData(double latitude, double longitude, double altitude, 
                double accuracy, FixType fixType, int satelliteCount)
    : latitude(latitude)
    , longitude(longitude)
    , altitude(altitude)
    , accuracy(accuracy)
    , fixType(fixType)
    , satelliteCount(satelliteCount)
{
}

bool GPSData::isValid() const {
    // Check latitude range (-90 to 90 degrees)
    if (latitude < -90.0 || latitude > 90.0) {
        return false;
    }
    
    // Check longitude range (-180 to 180 degrees)
    if (longitude < -180.0 || longitude > 180.0) {
        return false;
    }
    
    // Check altitude (Dead Sea is -430m, Mt. Everest is 8,848m, add margins)
    if (altitude < -500.0 || altitude > 9000.0) {
        return false;
    }
    
    // Check fix type (must not be NO_FIX)
    if (fixType == FixType::NO_FIX) {
        return false;
    }
    
    // Check if we have at least 3 satellites for a minimal fix
    if (satelliteCount < 3) {
        return false;
    }
    
    // All checks passed
    return true;
}

Vector3D GPSData::toENU(double referenceLatitude, double referenceLongitude, double referenceAltitude) const {
    // Convert degrees to radians
    double lat = deg2rad(latitude);
    double lon = deg2rad(longitude);
    double refLat = deg2rad(referenceLatitude);
    double refLon = deg2rad(referenceLongitude);
    
    // Calculate differences
    double dLat = lat - refLat;
    double dLon = lon - refLon;
    double dAlt = altitude - referenceAltitude;
    
    // Calculate east component
    double east = dLon * EARTH_RADIUS * std::cos(refLat);
    
    // Calculate north component
    double north = dLat * EARTH_RADIUS;
    
    // Up component is simply altitude difference
    double up = dAlt;
    
    return Vector3D(east, north, up);
}

void GPSData::fromENU(const Vector3D& enuPosition, double referenceLatitude, double referenceLongitude, double referenceAltitude) {
    // Extract ENU components
    double east = enuPosition.getX();
    double north = enuPosition.getY();
    double up = enuPosition.getZ();
    
    // Convert reference to radians
    double refLat = deg2rad(referenceLatitude);
    double refLon = deg2rad(referenceLongitude);
    
    // Calculate latitude change
    double dLat = north / EARTH_RADIUS;
    
    // Calculate longitude change
    double dLon = east / (EARTH_RADIUS * std::cos(refLat));
    
    // Convert back to degrees
    latitude = rad2deg(refLat + dLat);
    longitude = rad2deg(refLon + dLon);
    
    // Set altitude
    altitude = referenceAltitude + up;
}

double GPSData::distanceTo(const GPSData& other) const {
    // Haversine formula for distance between two points on a sphere
    
    // Earth radius in meters
    const double R = EARTH_RADIUS;
    
    // Convert latitude and longitude to radians
    double lat1 = deg2rad(latitude);
    double lon1 = deg2rad(longitude);
    double lat2 = deg2rad(other.latitude);
    double lon2 = deg2rad(other.longitude);
    
    // Differences
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    
    // Haversine formula
    double a = std::sin(dLat/2) * std::sin(dLat/2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dLon/2) * std::sin(dLon/2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1-a));
    double distance = R * c;
    
    // Add altitude difference using Pythagorean theorem
    double altDiff = other.altitude - altitude;
    distance = std::sqrt(distance*distance + altDiff*altDiff);
    
    return distance;
}