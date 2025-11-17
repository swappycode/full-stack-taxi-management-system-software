#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/listbox.h>
#include <wx/choice.h>
#include "Customer.h"
#include "Driver.h"
#include "Vehicle.h"
#include "Booking.h"

class MainFrame : public wxFrame {
private:
    // GUI Components
    wxPanel* mainPanel;
    wxNotebook* notebook;
    

    // Customer Panel Components
    wxPanel* customerPanel;
    wxTextCtrl* customerNameCtrl;
    wxTextCtrl* customerPhoneCtrl;
    wxTextCtrl* customerEmailCtrl;
    wxButton* addCustomerBtn;
    wxListBox* customerList;

    // Booking Panel Components
    wxPanel* bookingPanel;
    wxChoice* customerChoice;
    wxChoice* driverChoice;
    wxChoice* vehicleChoice;
    wxButton* bookRideBtn;
    wxChoice* dropLocationChoice;
    wxButton* completeRideBtn;
    wxStaticText* fareText;

    // Vehicle Panel Components
    wxPanel* vehiclePanel;
    wxTextCtrl* vehicleModelCtrl;
    wxTextCtrl* vehiclePlateCtrl;
    wxTextCtrl* vehicleTypeCtrl;
    wxButton* addVehicleBtn;
    wxListBox* vehicleList;

    // Driver Panel Components
    wxPanel* driverPanel;
    wxTextCtrl* driverNameCtrl;
    wxTextCtrl* driverPhoneCtrl;
    wxTextCtrl* driverLicenseCtrl;
    wxButton* addDriverBtn;
    wxListBox* driverList;
    int currentCustomerIndex;
    int currentDriverIndex;
    int currentVehicleIndex;
    Booking* currentBooking;

    // Initialization and Event Binding
    void InitializeComponents();
    void BindEvents();

    // Event Handlers
    void OnAddCustomer(wxCommandEvent& evt);
    void OnBookRide(wxCommandEvent& evt);
    void OnCompleteRide(wxCommandEvent& evt);
    void OnAddVehicle(wxCommandEvent& event);   // Event handler for adding vehicle
    void OnAddDriver(wxCommandEvent& event);    // Event handler for adding driver

public:
    MainFrame();
};

#endif 