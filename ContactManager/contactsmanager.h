#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <QString>

const std::string PATH{ "Resources/contacts.csv" };

struct Contact {
    std::string name;
    std::string number;
    std::string email;

    Contact() = default;
    Contact(std::string &name , std::string &number, std::string &email);
};


typedef std::vector<Contact> contacts;


class ContactsManager {
public :
    contacts contactList;
    Contact* SearchContact(const std::string& name);
    Contact splitString(std::string &token);
    void DeleteContact(const std::string& name);
    void EditContact(const std::string& name);

    contacts ReadContactsFromFile();
    void WriteContactsToFile(QString &info ,bool append);

    contacts GetContacts(); // A getter for the contact list


};
