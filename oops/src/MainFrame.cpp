#include "MainFrame.h"
#include <wx/filedlg.h>  
#include <wx/image.h>

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Taxi Management System",
    wxDefaultPosition, wxSize(800, 600)), currentBooking(nullptr) {
    InitializeComponents();
    BindEvents();
}

void MainFrame::InitializeComponents() {
    // Create main panel
    mainPanel = new wxPanel(this);

    // Create notebook
    notebook = new wxNotebook(mainPanel, wxID_ANY);

    // Create Customer Panel
    customerPanel = new wxPanel(notebook);
    wxBoxSizer* customerSizer = new wxBoxSizer(wxVERTICAL);

    // Customer input fields
    customerNameCtrl = new wxTextCtrl(customerPanel, wxID_ANY, "");
    customerPhoneCtrl = new wxTextCtrl(customerPanel, wxID_ANY, "");
    customerEmailCtrl = new wxTextCtrl(customerPanel, wxID_ANY, "");
    addCustomerBtn = new wxButton(customerPanel, wxID_ANY, "Add Customer");
    customerList = new wxListBox(customerPanel, wxID_ANY);

    customerSizer->Add(new wxStaticText(customerPanel, wxID_ANY, "Name:"), 0, wxALL, 5);
    customerSizer->Add(customerNameCtrl, 0, wxEXPAND | wxALL, 5);
    customerSizer->Add(new wxStaticText(customerPanel, wxID_ANY, "Phone:"), 0, wxALL, 5);
    customerSizer->Add(customerPhoneCtrl, 0, wxEXPAND | wxALL, 5);
    customerSizer->Add(new wxStaticText(customerPanel, wxID_ANY, "Email:"), 0, wxALL, 5);
    customerSizer->Add(customerEmailCtrl, 0, wxEXPAND | wxALL, 5);
    customerSizer->Add(addCustomerBtn, 0, wxALL, 5);
    customerSizer->Add(customerList, 1, wxEXPAND | wxALL, 5);

    customerPanel->SetSizer(customerSizer);

    // Create Booking Panel
    bookingPanel = new wxPanel(notebook);
    wxBoxSizer* bookingSizer = new wxBoxSizer(wxVERTICAL);

    customerChoice = new wxChoice(bookingPanel, wxID_ANY);
    driverChoice = new wxChoice(bookingPanel, wxID_ANY);
    vehicleChoice = new wxChoice(bookingPanel, wxID_ANY);
    bookRideBtn = new wxButton(bookingPanel, wxID_ANY, "Book Ride");
    dropLocationChoice = new wxChoice(bookingPanel, wxID_ANY);
    completeRideBtn = new wxButton(bookingPanel, wxID_ANY, "Complete Ride");
    fareText = new wxStaticText(bookingPanel, wxID_ANY, "Fare: Rs. 0.00");

    const std::vector<std::string>& locations = Booking::getDropLocations();
    for (const auto& location : locations) {
        dropLocationChoice->Append(location);
    }


    bookingSizer->Add(new wxStaticText(bookingPanel, wxID_ANY, "Select Customer:"), 0, wxALL, 5);
    bookingSizer->Add(customerChoice, 0, wxEXPAND | wxALL, 5);
    bookingSizer->Add(new wxStaticText(bookingPanel, wxID_ANY, "Select Driver:"), 0, wxALL, 5);
    bookingSizer->Add(driverChoice, 0, wxEXPAND | wxALL, 5);
    bookingSizer->Add(new wxStaticText(bookingPanel, wxID_ANY, "Select Vehicle:"), 0, wxALL, 5);
    bookingSizer->Add(vehicleChoice, 0, wxEXPAND | wxALL, 5);
    bookingSizer->Add(bookRideBtn, 0, wxALL, 5);
    bookingSizer->Add(new wxStaticText(bookingPanel, wxID_ANY,
        "Pickup Location: " + Booking::getPickupLocation()), 0, wxALL, 5);
    bookingSizer->Add(new wxStaticText(bookingPanel, wxID_ANY, "Select Drop Location:"), 0, wxALL, 5);
    bookingSizer->Add(dropLocationChoice, 0, wxEXPAND | wxALL, 5);
    bookingSizer->Add(completeRideBtn, 0, wxALL, 5);
    bookingSizer->Add(fareText, 0, wxALL, 5);

    bookingPanel->SetSizer(bookingSizer);

    // Create Vehicle Panel
    vehiclePanel = new wxPanel(notebook);
    wxBoxSizer* vehicleSizer = new wxBoxSizer(wxVERTICAL);

    vehicleModelCtrl = new wxTextCtrl(vehiclePanel, wxID_ANY, "");
    vehiclePlateCtrl = new wxTextCtrl(vehiclePanel, wxID_ANY, "");
    vehicleTypeCtrl = new wxTextCtrl(vehiclePanel, wxID_ANY, "");
    addVehicleBtn = new wxButton(vehiclePanel, wxID_ANY, "Add Vehicle");
    vehicleList = new wxListBox(vehiclePanel, wxID_ANY);

    vehicleSizer->Add(new wxStaticText(vehiclePanel, wxID_ANY, "Model:"), 0, wxALL, 5);
    vehicleSizer->Add(vehicleModelCtrl, 0, wxEXPAND | wxALL, 5);
    vehicleSizer->Add(new wxStaticText(vehiclePanel, wxID_ANY, "Plate Number:"), 0, wxALL, 5);
    vehicleSizer->Add(vehiclePlateCtrl, 0, wxEXPAND | wxALL, 5);
    vehicleSizer->Add(new wxStaticText(vehiclePanel, wxID_ANY, "Type:"), 0, wxALL, 5);
    vehicleSizer->Add(vehicleTypeCtrl, 0, wxEXPAND | wxALL, 5);
    vehicleSizer->Add(addVehicleBtn, 0, wxALL, 5);
    vehicleSizer->Add(vehicleList, 1, wxEXPAND | wxALL, 5);

    vehiclePanel->SetSizer(vehicleSizer);

    // Create Driver Panel
    driverPanel = new wxPanel(notebook);
    wxBoxSizer* driverSizer = new wxBoxSizer(wxVERTICAL);

    driverNameCtrl = new wxTextCtrl(driverPanel, wxID_ANY, "");
    driverPhoneCtrl = new wxTextCtrl(driverPanel, wxID_ANY, "");
    driverLicenseCtrl = new wxTextCtrl(driverPanel, wxID_ANY, "");
    addDriverBtn = new wxButton(driverPanel, wxID_ANY, "Add Driver");
    driverList = new wxListBox(driverPanel, wxID_ANY);

    driverSizer->Add(new wxStaticText(driverPanel, wxID_ANY, "Name:"), 0, wxALL, 5);
    driverSizer->Add(driverNameCtrl, 0, wxEXPAND | wxALL, 5);
    driverSizer->Add(new wxStaticText(driverPanel, wxID_ANY, "Phone:"), 0, wxALL, 5);
    driverSizer->Add(driverPhoneCtrl, 0, wxEXPAND | wxALL, 5);
    driverSizer->Add(new wxStaticText(driverPanel, wxID_ANY, "License:"), 0, wxALL, 5);
    driverSizer->Add(driverLicenseCtrl, 0, wxEXPAND | wxALL, 5);
    driverSizer->Add(addDriverBtn, 0, wxALL, 5);
    driverSizer->Add(driverList, 1, wxEXPAND | wxALL, 5);

    driverPanel->SetSizer(driverSizer);

    // Add panels to notebook
    notebook->AddPage(customerPanel, "Customers");
    notebook->AddPage(bookingPanel, "Bookings");
    notebook->AddPage(vehiclePanel, "Vehicles");
    notebook->AddPage(driverPanel, "Drivers");

    // Main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(notebook, 1, wxEXPAND);
    mainPanel->SetSizer(mainSizer);
}

void MainFrame::BindEvents() {
    addCustomerBtn->Bind(wxEVT_BUTTON, &MainFrame::OnAddCustomer, this);
    addVehicleBtn->Bind(wxEVT_BUTTON, &MainFrame::OnAddVehicle, this);
    addDriverBtn->Bind(wxEVT_BUTTON, &MainFrame::OnAddDriver, this);
    bookRideBtn->Bind(wxEVT_BUTTON, &MainFrame::OnBookRide, this);
    completeRideBtn->Bind(wxEVT_BUTTON, &MainFrame::OnCompleteRide, this);
}

// Customer, Vehicle, and Driver event handlers
void MainFrame::OnAddCustomer(wxCommandEvent& evt) {
    std::string name = customerNameCtrl->GetValue().ToStdString();
    std::string phone = customerPhoneCtrl->GetValue().ToStdString();
    std::string email = customerEmailCtrl->GetValue().ToStdString();

    if (name.empty() || phone.empty() || email.empty()) {
        wxMessageBox("Please fill all fields", "Error", wxOK | wxICON_ERROR);
        return;
    }

    std::string id = "C" + std::to_string(std::time(nullptr));
    Customer customer(id, name, phone, email);
    Customer::saveToCSV(customer);

    customerList->Append(name);
    customerChoice->Append(name);

    // Clear the text fields
    customerNameCtrl->SetValue("");
    customerPhoneCtrl->SetValue("");
    customerEmailCtrl->SetValue("");
}

void MainFrame::OnAddVehicle(wxCommandEvent& evt) {
    std::string model = vehicleModelCtrl->GetValue().ToStdString();
    std::string plate = vehiclePlateCtrl->GetValue().ToStdString();
    std::string type = vehicleTypeCtrl->GetValue().ToStdString();

    if (model.empty() || plate.empty() || type.empty()) {
        wxMessageBox("Please fill all fields", "Error", wxOK | wxICON_ERROR);
        return;
    }

    std::string id = "V" + std::to_string(std::time(nullptr));
    Vehicle vehicle(id, model, plate, type);
    Vehicle::saveToCSV(vehicle);

    vehicleList->Append(model);
    vehicleChoice->Append(model);

    // Clear the text fields
    vehicleModelCtrl->SetValue("");
    vehiclePlateCtrl->SetValue("");
    vehicleTypeCtrl->SetValue("");
}

void MainFrame::OnAddDriver(wxCommandEvent& evt) {
    std::string name = driverNameCtrl->GetValue().ToStdString();
    std::string phone = driverPhoneCtrl->GetValue().ToStdString();
    std::string license = driverLicenseCtrl->GetValue().ToStdString();

    if (name.empty() || phone.empty() || license.empty()) {
        wxMessageBox("Please fill all fields", "Error", wxOK | wxICON_ERROR);
        return;
    }

    std::string id = "D" + std::to_string(std::time(nullptr));
    Driver driver(id, name, phone, license);
    Driver::saveToCSV(driver);

    driverList->Append(name);
    driverChoice->Append(name);

    // Clear the text fields
    driverNameCtrl->SetValue("");
    driverPhoneCtrl->SetValue("");
    driverLicenseCtrl->SetValue("");
}

void MainFrame::OnBookRide(wxCommandEvent& evt) {
    int customerIndex = customerChoice->GetSelection();
    int driverIndex = driverChoice->GetSelection();
    int vehicleIndex = vehicleChoice->GetSelection();
    int locationIndex = dropLocationChoice->GetSelection();

    if (customerIndex == wxNOT_FOUND || driverIndex == wxNOT_FOUND ||
        vehicleIndex == wxNOT_FOUND || locationIndex == wxNOT_FOUND) {
        wxMessageBox("Please select all required fields", "Error", wxOK | wxICON_ERROR);
        return;
    }

    std::vector<Customer> customers = Customer::loadFromCSV();
    std::vector<Driver> drivers = Driver::loadFromCSV();
    std::vector<Vehicle> vehicles = Vehicle::loadFromCSV();

    std::string customerName = customers[customerIndex].getName();
    std::string driverName = drivers[driverIndex].getName();
    std::string vehiclePlate = vehicles[vehicleIndex].getPlateNumber();
    std::string dropLocation = dropLocationChoice->GetString(locationIndex).ToStdString();

    currentBooking = new Booking(customerName, driverName, vehiclePlate, dropLocation);
    double fare = currentBooking->getFare();

    wxMessageBox(wxString::Format(
        "Ride booked successfully!\n"
        "From: %s\n"
        "To: %s\n"
        "Fixed Fare: Rs. %.2f",
        Booking::getPickupLocation(),
        dropLocation,
        fare), "Booking Confirmation");
}




void MainFrame::OnCompleteRide(wxCommandEvent& evt) {
    if (!currentBooking) {
        wxMessageBox("No active booking found", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // Complete the ride
    currentBooking->completeRide();
    double fare = currentBooking->getFare();

    // Show fare
    wxMessageBox(wxString::Format(
        "Ride completed.\n"
        "From: %s\n"
        "To: %s\n"
        "Total fare: Rs. %.2f",
        Booking::getPickupLocation(),
        currentBooking->getDropLocation(),
        fare), "Ride Complete");

        
        

        // Payment option dialog
        wxMessageDialog paymentDialog(
            this,
            "Choose your payment method:",
            "Payment Options",
            wxYES_NO | wxCANCEL | wxCENTRE);
        paymentDialog.SetYesNoLabels("Card", "UPI");

        int response = paymentDialog.ShowModal();

        if (response == wxID_YES) {
            // Card Payment: Ask for card details
            wxTextEntryDialog cardDialog(this, "Enter your card number:", "Card Payment");
            if (cardDialog.ShowModal() == wxID_OK) {
                wxString cardNumber = cardDialog.GetValue();

                // Additional dialogs for CVV and Expiry Date
                wxTextEntryDialog cvvDialog(this, "Enter your card CVV:", "Card Payment");
                if (cvvDialog.ShowModal() == wxID_OK) {
                    wxString cardCVV = cvvDialog.GetValue();

                    wxTextEntryDialog expiryDialog(this, "Enter card expiry date (MM/YY):", "Card Payment");
                    if (expiryDialog.ShowModal() == wxID_OK) {
                        wxString cardExpiry = expiryDialog.GetValue();

                        // Check that all values are entered
                        if (!cardNumber.IsEmpty() && !cardCVV.IsEmpty() && !cardExpiry.IsEmpty()) {
                            wxMessageBox("Card details entered. Payment successful!", "Payment", wxOK | wxICON_INFORMATION);
                        }
                        else {
                            wxMessageBox("Incomplete card details. Payment failed.", "Payment", wxOK | wxICON_WARNING);
                        }
                    }
                }
            }
        }
        else if (response == wxID_NO) {
            // UPI Payment: Ask for UPI ID
            wxTextEntryDialog upiDialog(this, "Enter your UPI ID:", "UPI Payment");
            if (upiDialog.ShowModal() == wxID_OK) {
                wxString upiId = upiDialog.GetValue();
                if (!upiId.IsEmpty()) {
                    wxMessageBox("UPI ID entered. Payment successful!", "Payment", wxOK | wxICON_INFORMATION);
                }
                else {
                    wxMessageBox("No UPI ID entered. Payment failed.", "Payment", wxOK | wxICON_WARNING);
                }
            }
        }
        else {
            wxMessageBox("Payment cancelled.", "Payment", wxOK | wxICON_WARNING);
        }

        // Clear selections and clean up
        customerChoice->SetSelection(wxNOT_FOUND);
        driverChoice->SetSelection(wxNOT_FOUND);
        vehicleChoice->SetSelection(wxNOT_FOUND);


        delete currentBooking;
        currentBooking = nullptr;

    }

   


