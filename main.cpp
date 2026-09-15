#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Function for displaying menu
void displayMenu() {
    cout << "=================\n";
    cout << "   LogSentry\n";
    cout << "=================\n";
    cout << "\n";
    cout << "\n";
    cout << "1. Load log file\n";
    cout << "2. Display log summary\n";
    cout << "3. Search logs\n";
    cout << "4. Display suspicious events\n";
    cout << "5. Export report\n";
    cout << "6. Exit\n";
}

// Function for loading files into the program
void loadLogFile() {
    string filename;
    cout << "Upload your log file: \n";
    cin.ignore();
    getline(cin, filename);
    cout << "[" << filename << "]\n";
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file: " << filename << "\n";
    }
    else {
        cout << "Log file loaded \n";
    }
}


void displayLogSummary() {}

void searchLog() {}

void displaySuspiciousEvents() {}

void exportReport() {}


// Function  for when user selects menu option and call appropriate function
void menuSelection() {
    int selection;
    cout << "Selection: ";
    cin >> selection;
    cout << "You selected: " << selection << endl;
    if (selection == 1) {
        cout << "Load log file selected\n";
        loadLogFile();
    }
    else if (selection == 2) {
        cout << "Display log summary selected\n";
        displayLogSummary();
    }
    else if (selection == 3) {
        cout << "Search logs selected\n";
        searchLog();
    }
    else if (selection == 4) {
        cout << "Display suspicious events selected\n";
        displaySuspiciousEvents();
    }
    else if (selection == 5) {
        cout << "Export report\n";
        exportReport();
    }
    else if (selection == 6) {
        cout << "Exiting program\n";
    }
    else {
        cout << "Invalid selection\n";
    }
}



int main() {
    displayMenu();
    menuSelection();
    return 0;
}