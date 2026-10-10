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


class logSentry {
public:
    vector<LogEntry> logs;

    void displayLog(const LogEntry& log) {
        cout << log.ipAddress << " "
             << log.date << " "
             << log.event << " "
             << log.level << " "
             << log.username << " "
             << log.time << "\n";
    }


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
    };


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
                cout << "Log line number " << lineNum << " is malformed and was skipped. \n";
                continue;
            }
            cout << lineNum << ": " << line << "\n";
            logs.emplace_back(parsedLog);
        }
    }


    // Function allowing user to search through logs
    void searchLog() {
        int filterSelection;
        string ipAddrSelection;
        string dateSelection;
        string usernameSelection;
        string eventSelection;
        string levelSelection;
        string timeSelection;
        int matches = 0;

        cout << "How would you like to filter logs? \n";
        cout << "Select 1 to filter by IP address \n";
        cout << "Select 2 to filter by date \n";
        cout << "Select 3 to filter by username \n";
        cout << "Select 4 to filter by level \n";
        cout << "Select 5 to filter by event \n";
        cout << "Select 6 to filter by time \n";
        cin >> filterSelection;

        if (filterSelection == 1) {
            cout << "Enter IP address: \n";
            cin >> ipAddrSelection;
            for (const LogEntry& log : logs) {
                if (log.ipAddress == ipAddrSelection) {
                    matches++;
                    displayLog(log);
                }
            }
        }
        else if (filterSelection == 2) {
            cout << "Enter date: \n";
            cin >> dateSelection;
            for (const LogEntry& log : logs) {
                if (log.date == dateSelection) {
                    matches++;
                    displayLog(log);
                }
            }
        }
        else if (filterSelection == 3) {
            cout << "Enter username: \n";
            cin >> usernameSelection;
            for (const LogEntry& log : logs) {
                if (log.date == usernameSelection) {
                    matches++;
                    displayLog(log);
                }
            }
        }
        else if (filterSelection == 4) {
            cout << "Enter level: \n";
            cin >> levelSelection;
            for (const LogEntry& log : logs) {
                if (log.date == dateSelection) {
                    matches++;
                    displayLog(log);
                }
            }
        }
        else if (filterSelection == 5) {
            cout << "Enter event: \n";
            cin >> eventSelection;
            for (const LogEntry& log : logs) {
                if (log.date == dateSelection) {
                    matches++;
                    displayLog(log);
                }
            }
        }
        else if (filterSelection == 6) {
            cout << "Enter time: \n";
            cin >> timeSelection;
            for (const LogEntry& log : logs) {
                if (log.date == dateSelection) {
                    matches++;
                    displayLog(log);
                }
            }
        }
        if (matches == 0) {
            cout << "No matching selection found";
        }
    }



        // Function to parse lines
        vector<string> parse(const string& line, char delimiter) {
            vector<string> tokens;
            stringstream ss(line);
            string token;
            while (getline(ss, token, delimiter)) {
                tokens.push_back(token);
            }
            return tokens;
        }


        void displaySuspiciousEvents() {}
        void exportReport() {}
        void displayLogSummary() {}


        // Function  for when user selects menu option and calls appropriate function
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
