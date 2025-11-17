#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <fstream>

class Customer {
private:
    std::string id;
    std::string name;
    std::string phone;
    std::string email;

public:
    Customer(std::string id, std::string name, std::string phone, std::string email);
    static void saveToCSV(const Customer& customer);
    static std::vector<Customer> loadFromCSV();

    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }
    std::string getEmail() const { return email; }
};

#endif#pragma once
