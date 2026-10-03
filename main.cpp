#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


// Struct defining how each entry should look
struct LogEntry {
    string date;
    string time;
    string event;
    string level;
    string username;
    string ipAddress;

    explicit LogEntry(const vector<string>& vec) {
        if (vec.size() >= 6) {
            date = vec[0];
            time = vec[1];
            event = vec[2];
            level = vec[3];
            username = vec[4];
            ipAddress = vec[5];
        }
    }
    LogEntry() = default;
};


class logSentry{
public:
    vector<LogEntry> logs;


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
        menuSelection();
    }



    // Function for loading files into the program
     void loadLogFile() {
        LogEntry log;
        string filename;
        string line;
        cout << "Upload your log file: \n";
        cin.ignore();
        getline(cin, filename);
        cout << "You've uploaded " << "" << filename << " \n";
        std::ifstream file(filename);

        if (!file.is_open()) {
            cout << "Unable to open file: " << filename << "\n";
        }
        else {
            cout << "Log file loaded successfully \n";
        }
        int lineNum = 0;
        while (getline(file, line)) {
            lineNum++;
            vector<string> parsedLog = parse(line, ' ');
            if (parsedLog.size() != 6) {
                cout << "Log line number " << lineNum << " is malformed and was skipped." << "\n";
                continue;
            }
            cout << lineNum << ": " << line << "\n";
            logs.emplace_back(parsedLog);
        }

    }


    void displayLogSummary() {}

    void searchLog() {

    }

    vector<string> parse(const string& line, char delimiter) {
        vector<string> tokens;
        stringstream ss(line);
        string token;
        while (ss >> token, delimiter) {
                tokens.push_back(token);
        }
        return tokens;
    }

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
};




int main() {
    logSentry myLogSentry;
    myLogSentry.displayMenu();

        return 0;

}
