#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class Contact
{
private:
    string name;
    string phoneNumber;

public:
    Contact(string name = "", string phoneNumber = "")
    {
        this->name = name;
        this->phoneNumber = phoneNumber;
    }

    string getName() const
    {
        return name;
    }

    string getPhoneNumber() const
    {
        return phoneNumber;
    }

    void setName(string newName)
    {
        name = newName;
    }

    void setPhoneNumber(string newPhoneNumber)
    {
        phoneNumber = newPhoneNumber;
    }

    string serialize() const
    {
        return name + "," + phoneNumber;
    }

    static Contact deserialize(const string &line)
    {
        size_t comma = line.find(',');
        string name = line.substr(0, comma);
        string phone = line.substr(comma + 1);
        return Contact(name, phone);
    }
};

class ContactBook
{
private:
    vector<Contact> contacts;
    const string filename = "contacts.txt";

    static string toLower(const string &str)
    {
        string lower = str;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }

public:
    ContactBook()
    {
        loadFromFile();
    }

    void loadFromFile()
    {
        ifstream inFile(filename);
        string line;
        while (getline(inFile, line))
        {
            if (!line.empty())
            {
                contacts.push_back(Contact::deserialize(line));
            }
        }
        inFile.close();
    }

    void saveToFile()
    {
        ofstream outFile(filename, ios::trunc);
        for (const auto &contact : contacts)
        {
            outFile << contact.serialize() << endl;
        }
        outFile.close();
    }

    bool contactExists(const string &name)
    {
        string lowerName = toLower(name);
        for (const auto &contact : contacts)
        {
            if (toLower(contact.getName()) == lowerName)
            {
                return true;
            }
        }
        return false;
    }

    void addContact(const string &name, const string &phoneNumber)
    {
        if (contactExists(name))
        {
            cout << "Contact already exists with this name.\n";
            return;
        }
        contacts.push_back(Contact(name, phoneNumber));
        saveToFile();
        cout << "Contact added successfully.\n";
    }

    void editContact(const string &oldName, const string &newName, const string &newPhoneNumber)
    {
        for (auto &contact : contacts)
        {
            if (toLower(contact.getName()) == toLower(oldName))
            {
                contact.setName(newName);
                contact.setPhoneNumber(newPhoneNumber);
                saveToFile();
                cout << "Contact details updated successfully.\n";
                return;
            }
        }
        cout << "Contact not found.\n";
    }

    void deleteContact(const string &name)
    {
        for (auto it = contacts.begin(); it != contacts.end(); ++it)
        {
            if (toLower(it->getName()) == toLower(name))
            {
                contacts.erase(it);
                saveToFile();
                cout << "Contact deleted successfully.\n";
                return;
            }
        }
        cout << "Contact not found.\n";
    }

    void searchContact(const string &name)
    {
        bool found = false;
        for (const auto &contact : contacts)
        {
            if (toLower(contact.getName()).find(toLower(name)) != string::npos)
            {
                cout << "Name: " << contact.getName()
                     << ", Phone: " << contact.getPhoneNumber() << endl;
                found = true;
            }
        }
        if (!found)
        {
            cout << "No matching contact found.\n";
        }
    }

    void displayContacts() const
    {
        if (contacts.empty())
        {
            cout << "Contact book is empty.\n";
        }
        else
        {
            cout << "\nAll Contacts:\n";
            for (const auto &contact : contacts)
            {
                cout << "Name: " << contact.getName()
                     << ", Phone Number: " << contact.getPhoneNumber() << endl;
            }
        }
    }

    void deleteAllContacts()
    {
        contacts.clear();
        saveToFile();
        cout << "All contacts deleted successfully.\n";
    }
};

bool isValidPhoneNumber(const string &phone)
{
    return phone.length() == 10 && all_of(phone.begin(), phone.end(), ::isdigit);
}

int main()
{
    ContactBook contactBook;
    int choice;
    string name, phone, oldName, newName, newPhone;

    do
    {
        cout << "\n Contact Book Menu \n";
        cout << "1. Add Contact\n";
        cout << "2. Edit Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Search Contact\n";
        cout << "5. Display All Contacts\n";
        cout << "6. Delete All Contacts\n";
        cout << "7. Exit\n";
        cout << "Enter your choice (1 - 7): ";
        cin >> choice;
        cin.ignore(); // clear input buffer

        switch (choice)
        {
        case 1:
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter phone number (10 digits): ";
            getline(cin, phone);
            if (!isValidPhoneNumber(phone))
            {
                cout << "❌ Invalid phone number format.\n";
                break;
            }
            contactBook.addContact(name, phone);
            break;

        case 2:
            cout << "Enter existing contact name to edit: ";
            getline(cin, oldName);
            if (!contactBook.contactExists(oldName))
            {
                cout << "❌ Contact not found.\n";
                break;
            }
            cout << "Enter new name: ";
            getline(cin, newName);
            cout << "Enter new phone number: ";
            getline(cin, newPhone);
            if (!isValidPhoneNumber(newPhone))
            {
                cout << "❌ Invalid phone number format.\n";
                break;
            }
            contactBook.editContact(oldName, newName, newPhone);
            break;

        case 3:
            cout << "Enter name of contact to delete: ";
            getline(cin, name);
            contactBook.deleteContact(name);
            break;

        case 4:
            cout << "Enter name or part of name to search: ";
            getline(cin, name);
            contactBook.searchContact(name);
            break;

        case 5:
            contactBook.displayContacts();
            break;

        case 6:
            contactBook.deleteAllContacts();
            break;

        case 7:
            cout << "Exiting Contact Book. Goodbye! 👋\n";
            break;

        default:
            cout << "❌ Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
