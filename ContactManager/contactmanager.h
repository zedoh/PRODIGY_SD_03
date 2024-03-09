#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H
#include <QString>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <QObject>


struct Contact{
    QString* name;
    QString* phone ;
    QString* email;
    Contact(std::string &name ,std::string &number , std::string &eml) ;
    ~Contact() ;
};

typedef  std::vector<Contact*> contactList ;
typedef std::vector<QString> contactInfos;
class contactManager : public QObject
{
    Q_OBJECT ;
private:
    void SplitString(const std::string &info);
    void ClearCSV() ;
public:
   explicit contactManager(QObject *parent = nullptr);
    ~contactManager();

    contactList contacts ;

    // Reading and Writing Operations
    void WriteContact(QString& contactinfo, bool append);
    contactList ReadContact() ;
    Contact* getContactByName(const QString& name) ;
    void DeleteContact(const QString &contactName) ;
    void WriteContactList(const contactInfos &info) ; // trunc only
    void EditContact(QString& oldname , QString &newname , QString &newphone , QString &newemail);

};

#endif // CONTACTMANAGER_H
