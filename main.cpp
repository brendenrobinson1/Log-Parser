#include <iostream>
using namespace std;


// Function for displaying menu
void displayMenu() {
    cout << "=================" << endl;
    cout << "   LogSentry"<< endl;
    cout << "=================" << endl;
    cout << "\n";
    cout << "\n";
    cout << "1. Load log file" << endl;
    cout << "2. Display log summary" << endl;
    cout << "3. Search logs" << endl;
    cout << "4. Display suspicious events" << endl;
    cout << "5. Export report" << endl;
    cout << "6. Exit" << endl;
}

void loadLogFile() {}

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
        cout << "Load log file selected";
        loadLogFile();
    }
    else if (selection == 2) {
        cout << "Display log summary selected";
        displayLogSummary();
    }
    else if (selection == 3) {
        cout << "Search logs selected";
        searchLog();
    }
    else if (selection == 4) {
        cout << "Display suspicious events selected";
        displaySuspiciousEvents();
    }
    else if (selection == 5) {
        cout << "Export report";
        exportReport();
    }
    else if (selection == 6) {
        cout << "Exiting program";
    }
    else {
        cout << "Invalid selection" << endl;
    }
}



int main() {
    displayMenu();

return 0;
}