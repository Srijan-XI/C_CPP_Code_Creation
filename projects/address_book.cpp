#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

class AddressBook {
private:
    vector<Contact> contacts;
    const string filename = "contacts.txt";

public:
    AddressBook() {
        loadContacts();
    }

    void loadContacts() {
        ifstream file(filename);
        if (file.is_open()) {
            Contact contact;
            while (getline(file, contact.name)) {
                getline(file, contact.phone);
                getline(file, contact.email);
                contacts.push_back(contact);
            }
            file.close();
        }
    }

    void saveContacts() {
        ofstream file(filename);
        for (const auto& contact : contacts) {
            file << contact.name << endl;
            file << contact.phone << endl;
            file << contact.email << endl;
        }
        file.close();
    }

    void addContact() {
        Contact contact;
        cout << "Enter name: ";
        getline(cin, contact.name);
        cout << "Enter phone: ";
        getline(cin, contact.phone);
        cout << "Enter email: ";
        getline(cin, contact.email);
        contacts.push_back(contact);
        saveContacts();
        cout << "Contact added successfully!" << endl;
    }

    void viewContacts() const {
        if (contacts.empty()) {
            cout << "No contacts found." << endl;
            return;
        }
        cout << "\nContacts:\n";
        for (const auto& contact : contacts) {
            cout << "Name: " << contact.name 
                 << ", Phone: " << contact.phone 
                 << ", Email: " << contact.email 
                 << endl;
        }
    }

    void searchContact() const {
        string name;
        cout << "Enter the name to search: ";
        getline(cin, name);
        
        bool found = false;
        for (const auto& contact : contacts) {
            if (contact.name == name) {
                cout << "Found Contact - Name: " << contact.name 
                     << ", Phone: " << contact.phone 
                     << ", Email: " << contact.email 
                     << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Contact not found." << endl;
        }
    }

    void deleteContact() {
        string name;
        cout << "Enter the name of the contact to delete: ";
        getline(cin, name);

        auto it = remove_if(contacts.begin(), contacts.end(),
                            [&name](const Contact& c) { return c.name == name; });

        if (it != contacts.end()) {
            contacts.erase(it, contacts.end());
            saveContacts();
            cout << "Contact deleted successfully!" << endl;
        } else {
            cout << "Contact not found." << endl;
        }
    }
};

void printMenu() {
    cout << "\nAddress Book Menu\n";
    cout << "1. Add Contact\n";
    cout << "2. View Contacts\n";
    cout << "3. Search Contact\n";
    cout << "4. Delete Contact\n";
    cout << "5. Exit\n";
}

int main() {
    AddressBook addressBook;

    while (true) {
        printMenu();
        
        int choice;
        cout << "Choose an option (1-5): ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                addressBook.addContact();
                break;
            case 2:
                addressBook.viewContacts();
                break;
            case 3:
                addressBook.searchContact();
                break;
            case 4:
                addressBook.deleteContact();
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please select a valid option." << endl;
                break;
        }
    }

    return 0;
}
