#include "Booking.h"
#include <random>
Booking::Booking(std::string customerName, std::string driverName, std::string vehiclePlate)
    : customerName(customerName), driverName(driverName), vehiclePlate(vehiclePlate) {

    // Generate booking ID
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1000, 9999);
    bookingId = "B" + std::to_string(std::time(nullptr)) + std::to_string(dist(rng));

    bookingTime = std::time(nullptr);
    completed = false;
    distance = 0.0;
    fare = 0.0;
}

void Booking::calculateFare() {
    const double BASE_FARE = 50.0;
    const double PER_KM_RATE = 10.0;
    fare = BASE_FARE + (distance * PER_KM_RATE);
}

void Booking::completeRide(double distance) {
    this->distance = distance;
    calculateFare();
    completed = true;
    // No need to save anything to a file here
}