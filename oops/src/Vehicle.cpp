#include "Vehicle.h"
#include <fstream>

// Parameterized Constructor
Vehicle::Vehicle(std::string id, std::string model, std::string plateNumber, std::string type)
    : id(id), model(model), plateNumber(plateNumber), type(type), available(true) {}

// Static method to save Vehicle to a CSV file
void Vehicle::saveToCSV(const Vehicle& vehicle) {
    std::ofstream file("vehicles.csv", std::ios::app);
    if (file.is_open()) {
        std::ifstream infile("vehicles.csv");
        bool fileIsEmpty = infile.peek() == std::ifstream::traits_type::eof();

        if (fileIsEmpty) {
            // Write the header if the file is empty
            file << "ID,Model,PlateNumber,Type\n";
        }

        // Write vehicle data
        file << vehicle.getId() << ","
            << vehicle.getModel() << ","
            << vehicle.getPlateNumber() << ","
            << vehicle.getType() << "\n";

        file.close();
    }
}


// Static method to load Vehicles from CSV
std::vector<Vehicle> Vehicle::loadFromCSV() {
    std::vector<Vehicle> vehicles;
    std::ifstream file("vehicles.csv");
    if (file.is_open()) {
        std::string id, model, plateNumber, type;
        while (getline(file, id, ',') && getline(file, model, ',') &&
            getline(file, plateNumber, ',') && getline(file, type)) {
            vehicles.emplace_back(id, model, plateNumber, type);
        }
        file.close();
    }
    return vehicles;
}
