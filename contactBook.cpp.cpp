

    // This code represents a basic contact book application implemented in C++.
// It includes classes for Person, Contact, and ContactBook.
// - Person class represents a basic entity with a name.
// - Contact class, inheriting from Person, adds phone number functionality.
// - ContactBook class manages a collection of contacts and provides operations like adding, displaying,
//   editing, deleting, and searching contacts.
// The main function serves as the entry point to interact with the ContactBook functionalities.






#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Person {
public:
    string name;


    Person(string name) : name(name) {}

    string getName() {
        return name;
    }
    virtual void displayDetails() = 0;//virtual function
};

class Contact : public Person {
private:
    string phoneNumber;

public:
    Contact(string name, string phoneNumber) : Person(name), phoneNumber(phoneNumber) {}

    string getPhoneNumber() {
        return phoneNumber;
    }

    void setPhoneNumber(string newPhoneNumber) {
        phoneNumber = newPhoneNumber;
    }
    // overriding function
     void displayDetails() {
        cout << "Name: " << getName() << ", Phone Number: " << getPhoneNumber() << endl;
    }
    
       
};//end of contact

class ContactBook {
private:
    vector<Contact> contacts;

public:
//adding contacts
   inline void addContact(string name, string phoneNumber) {
        Contact newContact(name, phoneNumber);
        contacts.push_back(newContact);
        cout << "Contact added successfully." << endl;
    }
// searching contacts
  inline  bool search( string& name) {
        for (int i = 0; i < contacts.size(); ++i) {
            if (contacts[i].getName() == name) {
                return true;
            }
        }
        return false;
    }
//Edit contacts
    void editContact(string oldName, string newName, string newPhoneNumber) {
        bool found = false;
        for (int i = 0; i < contacts.size(); ++i) {
            if (contacts[i].getName() == oldName) {
                contacts[i].name = newName;
                contacts[i].setPhoneNumber(newPhoneNumber);
                cout << "Contact details updated successfully." << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
    }
//Delete contacts
    void deleteContact(const string& name) {
        bool found = false;
        for (int i = 0; i < contacts.size(); ++i) {
            if (contacts[i].getName() == name) {
                contacts.erase(contacts.begin() + i);
                cout << "Contact deleted successfully." << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
    }

     void searchContact( string& name) {
        bool found = false;
        for (int i = 0; i < contacts.size(); ++i) {
            if (contacts[i].getName() == name) {
                cout << "Contact found:" << endl;
                cout << "Name: " << contacts[i].getName() << ", Phone Number: " << contacts[i].getPhoneNumber() << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
     } 

     void displayContacts() {
        if (contacts.empty()) {
            cout << "Contact book is empty." << endl;
        } else {
            cout << "Contacts:" << endl;
            for (int i = 0; i < contacts.size(); ++i) {
               contacts[i].displayDetails();
            }
        }
    }

   
        friend void deleteAllContacts(ContactBook& book);//freind function
};//end of contactBook

//friend  function definition

void deleteAllContacts(ContactBook& book) {
    book.contacts.clear();
    cout << "All contacts deleted successfully." << endl;
}
  
    

  




int main() {
    ContactBook myContactBook;

    int choice;
    string name, phoneNumber, oldName, newName, newPhoneNumber;

    do {
        cout << "\nContact Book Menu:\n";
        cout << "1. Add Contact\n";
        cout << "2. Edit Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Search Contact\n";
        cout << "5. Display All Contacts\n";
        cout << "6. Delete All Contacts\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone number: ";
                cin >> phoneNumber;
                myContactBook.addContact(name, phoneNumber);
                break;
            case 2:
                cout << "Enter the name of the contact you want to edit: ";
                cin >> oldName;
                if (myContactBook.search(oldName)) {
                    cout << "Enter new name: ";
                    cin >> newName;
                    cout << "Enter new phone number: ";
                    cin >> newPhoneNumber;
                    myContactBook.editContact(oldName, newName, newPhoneNumber);
                } else {
                    cout << "Contact not found";
                }
                break;
            case 3:
                cout << "Enter the name of the contact you want to delete: ";
                cin >> name;
                myContactBook.deleteContact(name);
                break;
            case 4:
                cout << "Enter the name of the contact you want to search for: ";
                cin >> name;
                myContactBook.searchContact(name);
                break;
            case 5:
                myContactBook.displayContacts();
                break;
            case 6:
                deleteAllContacts(myContactBook);
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 7);

    return 0;
}
