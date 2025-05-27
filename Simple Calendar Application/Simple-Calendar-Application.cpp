// Simple Calendar Application in C++
// This program allows users to add, view, delete events on specific dates, and save/load events to/from a file.
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <algorithm>

using namespace std;

class Calendar {
private:
    map<string, vector<string>> events;

public:
    void addEvent(const string& date, const string& event) {
        events[date].push_back(event);
        sort(events[date].begin(), events[date].end());
        cout << "Event added to " << date << ".\n";
    }

    void viewEvents(const string& date) const {
        auto it = events.find(date);
        if (it != events.end()) {
            cout << "Events on " << date << " (" << it->second.size() << "):\n";
            for (const auto& ev : it->second) {
                cout << "- " << ev << "\n";
            }
        } else {
            cout << "No events found on " << date << ".\n";
        }
    }

    void viewAllEvents() const {
        if (events.empty()) {
            cout << "No events scheduled.\n";
            return;
        }
        cout << "All Scheduled Events:\n";
        for (const auto& [date, evList] : events) {
            cout << date << " (" << evList.size() << " events):\n";
            for (const auto& ev : evList) {
                cout << "  - " << ev << "\n";
            }
        }
    }

    void deleteEvent(const string& date, const string& event) {
        auto it = events.find(date);
        if (it != events.end()) {
            auto& evList = it->second;
            auto evIt = find(evList.begin(), evList.end(), event);
            if (evIt != evList.end()) {
                evList.erase(evIt);
                cout << "Event deleted from " << date << ".\n";
                if (evList.empty()) {
                    events.erase(it);
                }
            } else {
                cout << "Event not found on " << date << ".\n";
            }
        } else {
            cout << "No events found on " << date << ".\n";
        }
    }

    void saveEvents(const string& filename) const {
        ofstream ofs(filename);
        if (!ofs) {
            cerr << "Error saving events to file.\n";
            return;
        }
        for (const auto& [date, evList] : events) {
            for (const auto& ev : evList) {
                ofs << date << "|" << ev << "\n";
            }
        }
    }

    void loadEvents(const string& filename) {
        ifstream ifs(filename);
        if (!ifs) {
            return;
        }
        string line;
        while (getline(ifs, line)) {
            size_t pos = line.find('|');
            if (pos != string::npos) {
                string date = line.substr(0, pos);
                string ev = line.substr(pos + 1);
                events[date].push_back(ev);
            }
        }
        for (auto& [date, evList] : events) {
            sort(evList.begin(), evList.end());
        }
    }
};

bool isValidDate(const string& date) {
    const regex pattern(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!regex_match(date, pattern)) return false;

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (month < 1 || month > 12) return false;

    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (isLeap && month == 2)
        return day >= 1 && day <= 29;
    else
        return day >= 1 && day <= daysInMonth[month - 1];
}

int main() {
    Calendar cal;
    const string filename = "events.txt";
    cal.loadEvents(filename);

    int choice;
    string date, event;

    while (true) {
        cout << "\n--- Calendar Menu ---\n";
        cout << "1. Add Event\n";
        cout << "2. View Events on a Date\n";
        cout << "3. View All Events\n";
        cout << "4. Delete an Event\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
                if (!isValidDate(date)) {
                    cout << "Invalid date format or invalid date. Please try again.\n";
                    break;
                }
                cout << "Enter event description: ";
                getline(cin, event);
                if (event.empty()) {
                    cout << "Event description cannot be empty.\n";
                    break;
                }
                cal.addEvent(date, event);
                break;

            case 2:
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
                if (!isValidDate(date)) {
                    cout << "Invalid date format or invalid date. Please try again.\n";
                    break;
                }
                cal.viewEvents(date);
                break;

            case 3:
                cal.viewAllEvents();
                break;

            case 4:
                cout << "Enter date (YYYY-MM-DD) of event to delete: ";
                getline(cin, date);
                if (!isValidDate(date)) {
                    cout << "Invalid date format or invalid date. Please try again.\n";
                    break;
                }
                cout << "Enter exact event description to delete: ";
                getline(cin, event);
                if (event.empty()) {
                    cout << "Event description cannot be empty.\n";
                    break;
                }
                cal.deleteEvent(date, event);
                break;

            case 5:
                cal.saveEvents(filename);
                cout << "Events saved. Exiting Calendar. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
