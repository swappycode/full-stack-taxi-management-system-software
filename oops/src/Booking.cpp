#include "Booking.h"
#include <random>

// Define static members
const std::string Booking::PICKUP_LOCATION = "Nagpur Railway Station";

const std::map<std::string, double> Booking::LOCATION_FARES = {
    {"Buti Bori", 60.0},
    {"IIIT Nagpur", 100.0},
    {"Manewada", 30.0},
    {"Gadi Godam", 100.0},
    {"Laxmi Nagar", 70.0},
    {"Satgaon Fata", 40.0},
    {"Pipla Fata", 90.0},
    {"Besa-Pipla Road", 80.0},
    {"Hudkeshwar", 50.0}
};

const std::vector<std::string> Booking::DROP_LOCATIONS = {
    "Buti Bori",
    "IIIT Nagpur",
    "Manewada",
    "Gadi Godam",
    "Laxmi Nagar",
    "Satgaon Fata",
    "Pipla Fata",
    "Besa-Pipla Road",
    "Hudkeshwar"
};

Booking::Booking(std::string customerName, std::string driverName, std::string vehiclePlate, std::string dropLocation)
    : customerName(customerName), driverName(driverName), vehiclePlate(vehiclePlate), dropLocation(dropLocation) {

    // Generate booking ID
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1000, 9999);
    bookingId = "B" + std::to_string(std::time(nullptr)) + std::to_string(dist(rng));

    bookingTime = std::time(nullptr);
    completed = false;
    fare = getFareForLocation(dropLocation);
}

double Booking::getFareForLocation(const std::string& location) {
    auto it = LOCATION_FARES.find(location);
    if (it != LOCATION_FARES.end()) {
        return it->second;
    }
    return 0.0;
}

void Booking::completeRide() {
    completed = true;
}