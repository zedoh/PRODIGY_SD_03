#ifndef NEWCONTACTWIDGET_H
#define NEWCONTACTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QFormLayout>
#include "contactmanager.h"


class NewContactWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NewContactWidget(QWidget* parent = nullptr);

private slots:
    void onCancelClicked() ;
    void onSaveClicked();

private:
    QLineEdit* nameLineEdit;
    QLineEdit* phoneLineEdit;
    QLineEdit* emailLineEdit;
    QLabel* nameLabel ;
    QLabel* numberLabel ;
    QLabel* emailLabel ;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QVBoxLayout* layout;
    contactManager* cnt ;
signals:
    void UpdateCurrentList() ;

};

class EditContactWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditContactWidget(Contact* contact, contactManager* manager, QWidget *parent = nullptr);
    void setContactDetails(Contact* contact);

signals:
    void contactUpdated();

private slots:
    void onSaveClicked();

private:
    QLineEdit* nameEdit;
    QLineEdit* phoneEdit;
    QLineEdit* emailEdit;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    Contact* currentContact;
    contactManager* cntManager;
};

#endif // NEWCONTACTWIDGET_H
