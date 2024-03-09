#include "contactmanager.h"

const std::string path {"C:\\Programming\\projects\\Contacts Manager\\ContactManager\\users.csv"} ;

Contact::Contact(std::string &nam , std::string&number  , std::string &eml){
    name = new QString(QString::fromStdString(nam));
    phone = new QString(QString::fromStdString(number));
    email = new QString(QString::fromStdString(eml));
}
contactManager::contactManager(QObject *parent) {}

void contactManager::WriteContact(QString& contactinfo , bool append){
    auto status = std::ios::in | std::ios::app | std::ios::out ;
    if(!append){
        status = std::ios::in |std::ios::out|std::ios::trunc ;
    }
    std::fstream file(path.c_str(),status) ;
    if(file.fail()){
        std::cerr<<"\nCan't open the users file\n" ;
        return ;
    }

    file << contactinfo.toStdString() << '\n' ;
    SplitString(contactinfo.toStdString()) ;
    file.close();
}

void contactManager::SplitString(const std::string &info){
    std::istringstream iss(info) ;
    std::string token;
    std::string name ;
    getline(iss, token,',') ;
    name = token ;
    getline(iss,token, ',') ;
    std::string phone = token ;
    getline(iss,token, ',') ;
    std::string email = token ;


    Contact *cnt = new Contact(name, phone , email) ;
    contacts.push_back(cnt) ;
}


contactList contactManager::ReadContact(){
    contacts.clear();
    std::fstream file(path.c_str()) ;

    if(file.fail()){
        std::cerr<<"\nCouldn't open the contacts file\n" ;
        return contactList() ;
    }

    std::string token;
    while(getline(file,token)){
        SplitString(token) ;
    }


    file.close() ;
    return contacts;
}

Contact::~Contact(){
    delete name  ;
    delete phone ;
    delete email ;
}
Contact * contactManager::getContactByName(const QString& name){
    contactList list =ReadContact() ;
    for(auto &cnt : list){
        if(*cnt->name == name){
            return cnt ;
        }
    }
    return nullptr ;
}

contactManager::~contactManager(){
    for(auto &cnt : contacts){
        delete cnt ;
    }
}


void contactManager::WriteContactList(const std::vector<QString> &info){
    std::fstream file(path.c_str(), std::ios::out | std::ios::trunc);
    if(file.fail()){
        std::cerr << "\nError writing the file";
        return;
    }

    for(const auto &i : info){
        file << i.toStdString() << '\n';
    }
    file.close();
}

void contactManager::DeleteContact(const QString& contactName){
    contactList CONTACT;
    for(auto &cnt : contacts){
        if(*(cnt->name) == contactName){
            continue;
        }else{
            CONTACT.push_back(cnt);
        }
    }
    std::vector<QString> infos;
    for(auto &i : CONTACT){
        QString contactinfo = *(i->name) + ',' + *(i->phone) + ',' + *(i->email);
        infos.push_back(contactinfo);
    }
    WriteContactList(infos);
    contacts.clear();
    contacts = CONTACT;
}


void contactManager::EditContact(QString &oldname ,QString &newname , QString &newphone , QString &newemail){
    for(auto &cnt : contacts){
        if(*(cnt->name) == oldname){
            *(cnt->name)  = newname ;
            *(cnt->phone) = newphone;
            *(cnt->email) = newemail;
        }
    }
    std::vector<QString> infos;
    for(auto &i : contacts){
        QString contactinfo = *(i->name) + ',' + *(i->phone) + ',' + *(i->email);
        infos.push_back(contactinfo);
    }
    WriteContactList(infos);
}
