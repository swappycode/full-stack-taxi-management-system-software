#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <vector>
#include <fstream>

class Vehicle {
private:
    std::string id;
    std::string model;
    std::string plateNumber;
    std::string type;
    bool available;

public:
    // Default Constructor
    Vehicle() : available(true) {}

    // Parameterized Constructor
    Vehicle(std::string id, std::string model, std::string plateNumber, std::string type);

    // CSV File Operations
    static void saveToCSV(const Vehicle& vehicle);
    static std::vector<Vehicle> loadFromCSV();
   // static void updateCSV(const std::vector<Vehicle>& vehicles);

    // Availability
    void setAvailability(bool status) { available = status; }
    bool isAvailable() const { return available; }

    // Getters
    std::string getId() const { return id; }
    std::string getModel() const { return model; }
    std::string getPlateNumber() const { return plateNumber; }
    std::string getType() const { return type; }

    // ToString for displaying in ListBox
    std::string toString() const {
        return model + " (" + plateNumber + ")";
    }
};

#endif
