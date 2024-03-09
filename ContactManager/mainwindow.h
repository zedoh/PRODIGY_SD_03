#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QListView>
#include <QStringList>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QModelIndex>
#include <QPushButton>
#include <QDialog>
#include "newcontactwidget.h"
#include "contactmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void AddContactForm();
    void UpdateContactList() ;
    void onContactDoubleClick(const QModelIndex &index) ;
    void DeleteContactButton(const QString& contactName) ;

private:
    Ui::MainWindow *ui;

    QVBoxLayout *mainLayout;
    QListView* ListView;
    QStandardItemModel* MODEL;
    QWidget* centralWidget ;
    QPushButton* addnewcontact;
    contactManager* cntMng;
    QStringList* LIST ;
    NewContactWidget* cnt ;

    void SetupListView() ;
    void updateList() ;
    void showContactList() ;
    void refreshContactList() ;
};
#endif // MAINWINDOW_H
