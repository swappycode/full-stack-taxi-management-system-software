// Main.cpp
#include <wx/wx.h>
#include <wx/msgdlg.h>
#include "MainFrame.h"
#include "Customer.h"
#include "Driver.h"
#include "Vehicle.h"
#include "Booking.h"
#include <fstream>
#include <iostream>

class TaxiApp : public wxApp {
private:
    // Check if required files exist, create if they don't
    bool InitializeDataFiles() {
        std::vector<std::string> files = {
            "customers.csv",
            "drivers.csv",
            "vehicles.csv",
            
        };

        bool success = true;
        for (const auto& file : files) {
            std::ifstream checkFile(file);
            if (!checkFile.good()) {
                std::ofstream createFile(file);
                if (!createFile.good()) {
                    success = false;
                    wxMessageBox("Failed to create " + file, "Initialization Error",
                        wxOK | wxICON_ERROR);
                }
                else {
                    // Add headers to CSV files
                    if (file == "customers.csv") {
                        createFile << "ID,Name,Phone,Email\n";
                    }
                    else if (file == "drivers.csv") {
                        createFile << "ID,Name,Phone,License\n";
                    }
                    else if (file == "vehicles.csv") {
                        createFile << "ID,Model,PlateNumber,Type\n";
                    }
                    createFile.close();
                }
            }
            checkFile.close();
        }
        return success;
    }

public:
    virtual bool OnInit() {
        // Initialize the base wxApp
        if (!wxApp::OnInit()) {
            return false;
        }

        // Set application name for window title bar
        SetAppName("Taxi Management System");

        // Initialize data files
        if (!InitializeDataFiles()) {
            wxMessageBox("Failed to initialize required data files.\nThe application may not function correctly.",
                "Initialization Warning", wxOK | wxICON_WARNING);
        }

        try {
            // Create and show the main frame
            MainFrame* frame = new MainFrame();

            // Position the window in the center of the screen
            frame->Centre();

            // Show the frame
            frame->Show(true);

            // Set as top window
            SetTopWindow(frame);

            return true;
        }
        catch (const std::exception& e) {
            wxMessageBox(wxString::Format("Failed to initialize application: %s", e.what()),
                "Error", wxOK | wxICON_ERROR);
            return false;
        }
    }

    virtual int OnExit() {
        // Cleanup code here if needed
        return wxApp::OnExit();
    }

    virtual void OnUnhandledException() {
        wxMessageBox("An unhandled exception occurred.", "Error",
            wxOK | wxICON_ERROR);
    }

    virtual void OnFatalException() {
        wxMessageBox("A fatal error occurred.", "Fatal Error",
            wxOK | wxICON_ERROR);
    }
};

// Implement the Application
wxIMPLEMENT_APP(TaxiApp);