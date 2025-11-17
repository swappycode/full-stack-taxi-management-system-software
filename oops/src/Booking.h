#ifndef BOOKING_H
#define BOOKING_H
#include <string>
#include <ctime>
#include <map>
#include <vector>

class Booking {
private:
    std::string bookingId;
    std::string customerName;
    std::string driverName;
    std::string vehiclePlate;
    std::time_t bookingTime;
    std::string dropLocation;
    double fare;
    bool completed;

    // Static members for locations and fares
    static const std::string PICKUP_LOCATION;
    static const std::map<std::string, double> LOCATION_FARES;
    static const std::vector<std::string> DROP_LOCATIONS;

public:
    Booking(std::string customerName, std::string driverName, std::string vehiclePlate, std::string dropLocation);

    void completeRide();
    static const std::vector<std::string>& getDropLocations() { return DROP_LOCATIONS; }
    static const std::string& getPickupLocation() { return PICKUP_LOCATION; }
    static double getFareForLocation(const std::string& location);

    // Getters
    double getFare() const { return fare; }
    bool isCompleted() const { return completed; }
    std::string getDropLocation() const { return dropLocation; }
};

#endif