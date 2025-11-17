#include "Customer.h"

Customer::Customer(std::string id, std::string name, std::string phone, std::string email)
    : id(id), name(name), phone(phone), email(email) {}

void Customer::saveToCSV(const Customer& customer) {
    std::ofstream file("customers.csv", std::ios::app);
    if (file.is_open()) {
        file << customer.id << ","
            << customer.name << ","
            << customer.phone << ","
            << customer.email << "\n";
        file.close();
    }
}

std::vector<Customer> Customer::loadFromCSV() {
    std::vector<Customer> customers;
    std::ifstream file("customers.csv");
    std::string line;

    if (file.is_open()) {
        std::getline(file, line); // Skip the header line

        while (std::getline(file, line)) {
            size_t pos = 0;
            std::string token;
            std::string data[4];
            int index = 0;

            // Manually split the line by commas
            while ((pos = line.find(',')) != std::string::npos) {
                token = line.substr(0, pos);
                data[index++] = token;  // Store the token in the array
                line.erase(0, pos + 1);
            }
            // The last token (after the last comma)
            data[index] = line;

            // Now create a Customer object and add it to the vector
            customers.emplace_back(data[0], data[1], data[2], data[3]);
        }

        file.close();
    }
   

    return customers;
}
