#include "Driver.h"
#include <fstream>

// Parameterized Constructor
Driver::Driver(std::string id, std::string name, std::string phone, std::string license)
    : id(id), name(name), phone(phone), license(license), available(true) {}

// Static method to save Driver to a CSV file
void Driver::saveToCSV(const Driver& driver) {
    std::ofstream file("drivers.csv", std::ios::app);
    if (file.is_open()) {
        std::ifstream infile("drivers.csv");
        bool fileIsEmpty = infile.peek() == std::ifstream::traits_type::eof();

        if (fileIsEmpty) {
            // Write the header if the file is empty
            file << "ID,Name,Phone,License\n";
        }

        // Write driver data
        file << driver.getId() << ","
            << driver.getName() << ","
            << driver.getPhone() << ","
            << driver.getLicense() <<"\n";

        file.close();
    }
}
// Static method to load Drivers from CSV
std::vector<Driver> Driver::loadFromCSV() {
    std::vector<Driver> drivers;
    std::ifstream file("drivers.csv");
    if (file.is_open()) {
        std::string id, name, phone, license;
        while (getline(file, id, ',') && getline(file, name, ',') &&
            getline(file, phone, ',') && getline(file, license)) {
            drivers.emplace_back(id, name, phone, license);
        }
        file.close();
    }
    return drivers;
}
