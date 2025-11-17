#ifndef BOOKING_H
#define BOOKING_H
#include <string>
#include <ctime>
#include <fstream>
#include "Customer.h"
#include "Driver.h"
#include "Vehicle.h"
#include <vector>

class Booking {
private:
    std::string bookingId;
    std::string customerName;  // Directly store customer name
    std::string driverName;    // Directly store driver name
    std::string vehiclePlate;  // Directly store vehicle plate number
    std::time_t bookingTime;
    double distance;
    double fare;
    bool completed;

public:
    // Constructor accepts actual names and vehicle plate
    Booking(std::string customerName, std::string driverName, std::string vehiclePlate);

    void calculateFare();
    void completeRide(double distance);

    // Getters
    double getFare() const { return fare; }
    bool isCompleted() const { return completed; }
};

#endif