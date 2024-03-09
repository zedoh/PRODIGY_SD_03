#include "newcontactwidget.h"

NewContactWidget::NewContactWidget(QWidget*parent):QWidget(parent, Qt::Window | Qt::WindowCloseButtonHint){
    layout = new QVBoxLayout(this);
    nameLineEdit = new QLineEdit(this);
    phoneLineEdit = new QLineEdit(this);
    emailLineEdit = new QLineEdit(this);
    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel",this);

    // contact manager for handling the reading and writing user info in the CSV file
    cnt = new contactManager() ;

    nameLabel = new QLabel("name: ",this) ;
    numberLabel = new QLabel("number: ",this) ;
    emailLabel = new QLabel("email: ",this) ;

    QFormLayout *formLayout = new QFormLayout();

    formLayout->addRow(nameLabel,nameLineEdit) ;
    formLayout->addRow(numberLabel,phoneLineEdit) ;
    formLayout->addRow(emailLabel,emailLineEdit) ;

    QHBoxLayout* buttonLayout = new QHBoxLayout() ;
    buttonLayout->addWidget(saveButton) ;
    buttonLayout->addWidget(cancelButton) ;

    layout->addLayout(formLayout) ;
    layout->addLayout(buttonLayout);

    setLayout(layout);
    setWindowTitle("Add New Contact");
    setFixedSize(300, 200);

    // firing a signale when cancel button is clicked
    connect(cancelButton, &QPushButton::clicked, this , &NewContactWidget::onCancelClicked) ;

    // firing a signale when save button is clicked
    connect(saveButton , &QPushButton::clicked, this , &NewContactWidget::onSaveClicked);

    setWindowModality(Qt::ApplicationModal);
}

void NewContactWidget::onCancelClicked(){
    this->close() ;
}

void NewContactWidget::onSaveClicked(){
    QString name = nameLineEdit->text() ;
    QString number = phoneLineEdit->text() ;
    QString email = emailLineEdit->text() ;
    QString info = name+','+number+','+email ;
    cnt->WriteContact(info,true) ;
    emit UpdateCurrentList() ;
    this->close() ;
}


EditContactWidget::EditContactWidget(Contact* contact, contactManager* manager, QWidget *parent)
    : QWidget(parent, Qt::Window | Qt::WindowCloseButtonHint), currentContact(contact), cntManager(manager)
{
    qDebug() << "EditContactWidget: Constructor called";
    QVBoxLayout* layout = new QVBoxLayout(this);

    nameEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);
    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);

    layout->addWidget(nameEdit);
    layout->addWidget(phoneEdit);
    layout->addWidget(emailEdit);
    layout->addWidget(saveButton);
    layout->addWidget(cancelButton);

    setLayout(layout);

    setContactDetails(contact);

    connect(saveButton, &QPushButton::clicked, this, &EditContactWidget::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &EditContactWidget::close);
}

void EditContactWidget::setContactDetails(Contact* contact)
{
    if (contact != nullptr) {
        nameEdit->setText(*contact->name);
        phoneEdit->setText(*contact->phone);
        emailEdit->setText(*contact->email);
    }
}

void EditContactWidget::onSaveClicked()
{
    QString newName = nameEdit->text();
    QString newPhone = phoneEdit->text();
    QString newEmail = emailEdit->text();
    QString oldname =  *currentContact->name ;
    *currentContact->name = newName;
    *currentContact->phone = newPhone;
    *currentContact->email = newEmail;

    cntManager->EditContact(oldname , newName , newPhone, newEmail);

    emit contactUpdated();
    close();
}
