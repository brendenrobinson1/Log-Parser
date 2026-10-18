#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
bool keepRunning = true;


// struct defining how each entry should look
struct LogEntry {
    string date;
    string time;
    string level;
    string event;
    string user;
    string ip;

    // constructor stripping prefixes and initializing data
    explicit LogEntry(const vector<string>& vec) {
        if (vec.size() >= 6) {
            if (vec[0].find('=') != string::npos) {
                date = vec[0].substr(vec[0].find('=')+1);
            }
            else {
                date = vec[0];
            }
            if (vec[1].find('=') != string::npos) {
                time = vec[1].substr(vec[1].find('=')+1);
            }
            else {
                time = vec[1];
            }
            if (vec[2].find('=') != string::npos) {
                level = vec[2].substr(vec[2].find('=')+1);
            }
            else {
                level = vec[2];
            }
            if (vec[3].find('=') != string::npos) {
                event = vec[3].substr(vec[3].find('=')+1);
            }
            else {
                event = vec[3];
            }
            if (vec[4].find('=') != string::npos) {
                user = vec[4].substr(vec[4].find('=') + 1);
            } else {
                user = vec[4];
            }
            if (vec[5].find('=') != string::npos) {
                ip = vec[5].substr(vec[5].find('=')+1);
            }
            else {
                ip = vec[5];
            }
        }
    }
    LogEntry() = default;
};


class logSentry {
public:
    // vector to store log entry objects
    vector<LogEntry> logs;


    // function for displaying menu
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
        cout << "\n";
        menuSelection();
    }


    // function for loading files into the program
    void loadLogFile() {
        LogEntry log;
        string filename;
        string line;
        string retry;
        string moreLogs;

        cout << "Upload your log file: \n";
        cin.ignore();
        getline(cin, filename);
        cout << "You've uploaded " << "" << filename << " \n";
        std::ifstream file(filename);

        if (!file.is_open()) {
            cout << "Unable to open file: " << filename << "\n";
            cout << "Would you like to try again? [Y/N] \n";
            cin >> retry;
            if (retry == "Y" || retry == "y") {
                loadLogFile();
            }
            else {
                return;
            }
        }
        else
            {
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
        cout << "Do you have any more logs to upload? [Y/N] \n";
        cin >> moreLogs;
        if (moreLogs == "Y") {
            loadLogFile();
        }
    }

    // helper function for search logs function
    void displayLog(const LogEntry& log) {
        cout << log.ip << " "
             << log.date << " "
             << log.event << " "
             << log.level << " "
             << log.user << " "
             << log.time << "\n";
    }


    // function allowing user to search through logs and filter by token
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
        cout << "Select 7 to display the main menu \n";
        cin >> filterSelection;

        if (filterSelection == 1) {
            cout << "Enter IP address: \n";
            cin >> ipAddrSelection;
            for (const LogEntry& log : logs) {
                if (log.ip == ipAddrSelection) {
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
                if (log.user == usernameSelection) {
                    matches++;
                    displayLog(log);
                }
            }
        }
        else if (filterSelection == 4) {
            cout << "Enter level: \n";
            cin >> levelSelection;
            for (const LogEntry& log : logs) {
                if (log.level == levelSelection) {
                    matches++;
                    displayLog(log);
                }
            }
        }
        else if (filterSelection == 5) {
            cout << "Enter event: \n";
            cin >> eventSelection;
            for (const LogEntry& log : logs) {
                if (log.event == eventSelection) {
                    matches++;
                    displayLog(log);
                }
            }
        }
        else if (filterSelection == 6) {
            cout << "Enter time: \n";
            cin >> timeSelection;
            for (const LogEntry& log : logs) {
                if (log.time == timeSelection) {
                    matches++;
                    displayLog(log);
                }
            }
        }
        else if (filterSelection == 7) {
            displayMenu();
        }
        if (matches == 0) {
            cout << "No matching selection found";
        }
    }


    // function to parse lines
    vector<string> parse(const string& line, char delimiter) {
        vector<string> tokens;
        stringstream ss(line);
        string token;
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }


    // function displaying suspicious login activity
    void displaySuspiciousEvents() {
        int suspiciousLoginsCount = 0;
        unordered_map<string, int> susIpAddresses;
        unordered_map<string, int> susUsers;

        for (const LogEntry& log: logs) {
            if (log.level == "ERROR" && log.event == "login") {
                susIpAddresses[log.ip]++;
            }
            else if (log.level == "INFO" && log.event == "login") {
                if ( susIpAddresses.contains((log.ip) ) && susIpAddresses.at(log.ip) >= 3) {
                    suspiciousLoginsCount++;
                }
            }
        }

        cout << "Successful logins after 3+ failed attempts:  " << suspiciousLoginsCount << "\n";

		for (const auto& entry : susIpAddresses) {
			if (entry.second >= 3) {
			    cout << "suspicious " << entry.first << "\n";
			}
		}
    }


    // function to display log summary
    void displayLogSummary() {
        unordered_set<string> uniqueIpAddresses;
        unordered_set<string> uniqueUsers;
        int successLogin = 0;
        int failureLogin = 0;
        int info = 0;
        int warning = 0;

        for (const LogEntry& log : logs) {
            if (log.level == "WARN") {
                warning++;
            }
            if (log.event == "login" && log.level == "ERROR") {
                failureLogin++;
            }
            if (log.level == "INFO") {
                info++;
            }
            if (log.event == "login" && log.level == "INFO") {
                successLogin++;
            }
            uniqueIpAddresses.insert(log.ip);
            uniqueUsers.insert(log.user);
        }
        
            cout << "There were " << uniqueIpAddresses.size() << " unique IP addresses \n";
            cout << "There were " << uniqueUsers.size() << " unique usernames \n";
            cout << "There were " << info << " informational events \n";
            cout << "There were " << failureLogin << " failures \n";
            cout << "There were " << successLogin << " successful logins \n";
            cout << "There were " << warning << " warnings \n";
    }


    // function to create and export a report containing statistics about the log entry
    void exportReport() {
        unordered_set<string> uniqueIpAddresses;
        unordered_set<string> uniqueUsers;
        unordered_map<string, int> susIpAddresses;
        int info = 0;
        int warning = 0;
        int failedLogins = 0;
        int successfulLogin = 0;
        int suspiciousLoginsExport = 0;
        int susIpCount = 0;

        ofstream report("LogSentry_Report.txt");
        if (!report.is_open()) {
            cout << "Unable to open logsentry_report.txt";
            return;
        }

        for (const LogEntry& log : logs) {
            if (log.level == "INFO") {
                info++;
            }
            if (log.level == "WARN") {
                warning++;
            }
            if (log.event == "login" && log.level == "ERROR") {
                failedLogins++;
                susIpAddresses[log.ip]++;
            }
            if (log.event == "login" && log.level == "INFO") {
                successfulLogin++;
            }
        }
        
        for (const LogEntry& log : logs) {
            uniqueIpAddresses.insert(log.ip);
            uniqueUsers.insert(log.user);
        }
        
        for (const auto& entry : susIpAddresses) {
            if (entry.second >= 3) {
                susIpCount++;
            }
        }
        
        for (const LogEntry& log: logs) {
            if (log.level == "INFO" && log.event == "login") {
                if ( susIpAddresses.contains((log.ip) ) && susIpAddresses.at(log.ip) >= 3) {
                    suspiciousLoginsExport++;
                }
            }
        }
        
            report << "========= LogSentry Report =======\n";
            report << "\n";
            report << "\n";
            cout << "Report generated successfully. \n";
            report << "\n";
            report << "There were " << logs.size() << " logs generated successfully.\n";
            report << "\n";
            report << "There were " << uniqueIpAddresses.size() << " unique ip addresses. \n";
            report << "\n";
            report << "There were " << uniqueUsers.size() << " unique usernames. \n";
            report << "\n";
            report << "There were " << info << " informational events. \n";
            report << "\n";
            report << "There were " << warning << " warnings. \n";
            report << "\n";
            report << "There were " << failedLogins << " failed login attempts. \n";
            report << "\n";
            report << "There were " << successfulLogin << " successful logins. \n";
            report << "\n";
            report << "IPs with 3+ failed login attempts: " << susIpCount <<"\n";
            report << "\n";
            report << "Successful logins after 3+ failures: " << suspiciousLoginsExport << "\n";
    }

    // function  for when user selects menu option and calls appropriate function
    void menuSelection() {
        int selection;
        cout << "Selection: ";
        cin >> selection;
        cout << "You selected: " << selection << "\n";
        cout << "\n";
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
            keepRunning = false;

        }
        else {
            cout << "Invalid selection\n";
        }
    }
};



    int main() {
        logSentry myLogSentry;
        while (keepRunning) {
            myLogSentry.displayMenu();
        }
        return 0;
    }
