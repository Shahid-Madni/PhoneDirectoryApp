#include <iostream>
#include <list>
#include <string>

using namespace std;

class Contact {
private:
    string firstName;
    string lastName;
    string mobile;
    string home;
    string work;
    string email;

public:
    Contact(const string& fName, const string& lName, const string& mobileNumber,
            const string& homeNumber, const string& workNumber, const string& emailAddress)
        : firstName(fName), lastName(lName), mobile(mobileNumber),
          home(homeNumber), work(workNumber), email(emailAddress) {}

    void display() const {
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Mobile: " << mobile << endl;
        cout << "Home: " << home << endl;
        cout << "Work: " << work << endl;
        if (!email.empty()) {
            cout << "Email: " << email << endl;
        }
    }

    string getFirstName() const {
        return firstName;
    }

    string getLastName() const {
        return lastName;
    }

    string getMobile() const {
        return mobile;
    }

    void updateContact(const string& fName, const string& lName, const string& mobileNumber,
                       const string& homeNumber, const string& workNumber, const string& emailAddress) {
        firstName = fName;
        lastName = lName;
        mobile = mobileNumber;
        home = homeNumber;
        work = workNumber;
        email = emailAddress;
    }

    bool matchesQuery(const string& query) const {
        return firstName.find(query) != string::npos ||
               lastName.find(query) != string::npos ||
               mobile.find(query) != string::npos;
    }
};

class PhoneDirectory {
private:
    list<Contact> contacts;

public:
    void addContact(const Contact& contact) {
        contacts.push_back(contact);
    }

    void editContact(const string& mobile, const Contact& updatedContact) {
        for (auto& contact : contacts) {
            if (contact.getMobile() == mobile) {
                contact = updatedContact;
                return;
            }
        }
        cout << "Contact not found!" << endl;
    }

    void deleteContact(const string& mobile) {
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->getMobile() == mobile) {
                contacts.erase(it);
                cout << "Contact deleted." << endl;
                return;
            }
        }
        cout << "Contact not found!" << endl;
    }

    void searchContacts(const string& query) const {
        for (const auto& contact : contacts) {
            if (contact.matchesQuery(query)) {
                contact.display();
                cout << "---------------------" << endl;
            }
        }
    }

    void displayContacts() const {
        for (const auto& contact : contacts) {
            contact.display();
            cout << "---------------------" << endl;
        }
    }

    void sortContactsByName() {
        contacts.sort([](const Contact& a, const Contact& b) {
            if (a.getLastName() != b.getLastName()) return a.getLastName() < b.getLastName();
            return a.getFirstName() < b.getFirstName();
        });
    }

    void sortContactsByPhoneNumber() {
        contacts.sort([](const Contact& a, const Contact& b) {
            return a.getMobile() < b.getMobile();
        });
    }
};

int main() {
    PhoneDirectory directory;
    int choice;

    do {
        cout << "\nPhone Directory Application\n";
        cout << "1. Add Contact\n";
        cout << "2. Edit Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Search Contacts\n";
        cout << "5. Display All Contacts\n";
        cout << "6. Sort Contacts by Name\n";
        cout << "7. Sort Contacts by Phone Number\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer

        if (choice == 1) {
            string firstName, lastName, mobile, home, work, email;
            cout << "Enter First Name: ";
            getline(cin, firstName);
            cout << "Enter Last Name: ";
            getline(cin, lastName);
            cout << "Enter Mobile Number: ";
            getline(cin, mobile);
            cout << "Enter Home Number: ";
            getline(cin, home);
            cout << "Enter Work Number: ";
            getline(cin, work);
            cout << "Enter Email (optional): ";
            getline(cin, email);
            Contact contact(firstName, lastName, mobile, home, work, email);
            directory.addContact(contact);
        } else if (choice == 2) {
            string mobile;
            cout << "Enter Mobile Number of the Contact to Edit: ";
            getline(cin, mobile);
            string firstName, lastName, newMobile, home, work, email;
            cout << "Enter First Name: ";
            getline(cin, firstName);
            cout << "Enter Last Name: ";
            getline(cin, lastName);
            cout << "Enter New Mobile Number: ";
            getline(cin, newMobile);
            cout << "Enter Home Number: ";
            getline(cin, home);
            cout << "Enter Work Number: ";
            getline(cin, work);
            cout << "Enter Email (optional): ";
            getline(cin, email);
            Contact updatedContact(firstName, lastName, newMobile, home, work, email);
            directory.editContact(mobile, updatedContact);
        } else if (choice == 3) {
            string mobile;
            cout << "Enter Mobile Number of the Contact to Delete: ";
            getline(cin, mobile);
            directory.deleteContact(mobile);
        } else if (choice == 4) {
            string query;
            cout << "Enter Name or Phone Number to Search: ";
            getline(cin, query);
            directory.searchContacts(query);
        } else if (choice == 5) {
            directory.displayContacts();
        } else if (choice == 6) {
            directory.sortContactsByName();
            cout << "Contacts sorted by name." << endl;
        } else if (choice == 7) {
            directory.sortContactsByPhoneNumber();
            cout << "Contacts sorted by phone number." << endl;
        }
    } while (choice != 0);

    return 0;
}
