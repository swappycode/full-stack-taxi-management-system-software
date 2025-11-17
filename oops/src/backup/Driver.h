#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <vector>
#include <fstream>

class Driver {
private:
    std::string id;
    std::string name;
    std::string phone;
    std::string license;
    bool available;

public:
    // Default Constructor
    Driver() : available(true) {}

    // Parameterized Constructor
    Driver(std::string id, std::string name, std::string phone, std::string license);

    // CSV File Operations
    static void saveToCSV(const Driver& driver);
    static std::vector<Driver> loadFromCSV();

    // Availability
    void setAvailability(bool status) { available = status; }
    bool isAvailable() const { return available; }
    //static void updateCSV(const std::vector<Driver>& drivers);
    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }
    std::string getLicense() const { return license; }

    // ToString for displaying in ListBox
    std::string toString() const {
        return name + " (License: " + license + ")";
    }
};

#endif
