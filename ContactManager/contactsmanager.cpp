#include "contactsmanager.h"


Contact::Contact(std::string& name, std::string& number, std::string& email) : name(name) , number(number),email(email)
{
}

Contact* ContactsManager::SearchContact(const std::string& name)
{
    for (auto& cnt : contactList)
        if (cnt.name == name)
            return &cnt;

    return nullptr;
}

Contact ContactsManager::splitString(std::string& token)
{
    std::istringstream iss(token);
    Contact cnt;
    getline(iss,token, ',');
    cnt.name = token;
    getline(iss,token, ',');
    cnt.number = token;
    getline(iss,token, ',');
    cnt.email = token;
    return cnt;
}




contacts ContactsManager::ReadContactsFromFile()
{
    std::fstream file(PATH.c_str());
    if (file.fail()) {
        std::cerr << "\nCan't open the contacts file\n";
        return contacts();
    }
    std::string token;
    while(getline(file,token)) {
        Contact cnt = splitString(token);
        contactList.push_back(cnt);
    }

    file.close();
    return contactList;
}

void ContactsManager::WriteContactsToFile(QString& info ,bool append)
{
    auto status = std::ios::in| std::ios::out | std::ios::app;
    if (!append)
        status = std::ios::in | std::ios::out | std::ios::trunc;
    std::fstream file(PATH.c_str() , status);
    if (file.fail()) {
        std::cerr << "\nCan't open the contacts file\n";
        return;
    }

    file.close();
    return;
}

contacts ContactsManager::GetContacts()
{
    return contactList;
}


void ContactsManager::DeleteContact(const std::string& name)
{
    contacts UpdatedList;
    for (auto& cnt : contactList) {
        if (cnt.name == name) {
            continue;
        }
        else {
            UpdatedList.push_back(cnt);
        }
    }
    contactList.clear();
    contactList = UpdatedList;

}
