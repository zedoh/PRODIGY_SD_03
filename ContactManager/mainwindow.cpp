#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MODEL = new QStandardItemModel(this);
    SetupListView() ;
    connect(addnewcontact,&QPushButton::clicked,this,&MainWindow::AddContactForm);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::SetupListView(){
    MainWindow::setFixedSize(405,605);
    MainWindow::setWindowTitle("My Contacts");
    cntMng = new contactManager() ;
    centralWidget = new QWidget(this) ;
    centralWidget->setFixedSize(QSize(400,600)) ;
    ListView = new QListView(centralWidget) ;
    mainLayout = new QVBoxLayout(centralWidget) ;
    addnewcontact = new QPushButton("Add New Contact") ;
    mainLayout->addWidget(ListView) ;
    mainLayout->addWidget(addnewcontact) ;
    setCentralWidget(centralWidget);
    showContactList();
    connect(ListView , &QListView::doubleClicked, this ,&MainWindow::onContactDoubleClick);

}

void MainWindow::AddContactForm(){
   NewContactWidget* cnt = new NewContactWidget(this) ;
    cnt->setAttribute(Qt::WA_DeleteOnClose);
    cnt->show();
    connect(cnt , &NewContactWidget::UpdateCurrentList , this , &MainWindow::UpdateContactList);
}

void MainWindow::showContactList(){
    contactList list = cntMng->ReadContact()  ;
    if(list.empty()){
        return ;
    }
    for(auto &contact : list){
        QStandardItem* item  = new QStandardItem(*(contact->name));
        item->setEditable(false) ; //Prevent the user from editing the contact directly from the list view
        MODEL->appendRow(item);
    }
    ListView->setModel(MODEL);
}

void MainWindow::UpdateContactList(){
    contactList list = cntMng->ReadContact();
    Contact* cnt  = list.back() ;

    QStandardItem *item = new QStandardItem(*(cnt->name)) ;
    item->setEditable(false) ;
    MODEL->appendRow(item) ;
    ListView->setModel(MODEL) ;
}

void MainWindow::onContactDoubleClick(const QModelIndex &index){
    if (!index.isValid()) {
        return;
    }

    QString contactName = MODEL->data(index, Qt::DisplayRole).toString();
    Contact* contact = cntMng->getContactByName(contactName);

    if (contact != nullptr) {
        // Create a dialog or another window to show the contact details
        QDialog* detailsDialog = new QDialog(this);
        detailsDialog->setFixedSize(200,200) ;
        QVBoxLayout* layout = new QVBoxLayout(detailsDialog);

        // Add widgets to display contact information
        layout->addWidget(new QLabel("Name: " + *contact->name));
        layout->addWidget(new QLabel("Phone: " + *contact->phone));
        layout->addWidget(new QLabel("Email: " + *contact->email));

        QPushButton* closeButton = new QPushButton("Close", detailsDialog);
        QPushButton* editButton = new QPushButton("Edit", detailsDialog);
        QPushButton* deleteButton = new QPushButton("Delete", detailsDialog);

        QHBoxLayout* buttonsLayout = new QHBoxLayout() ;

        connect(closeButton, &QPushButton::clicked, detailsDialog, &QDialog::accept);
        connect(deleteButton, &QPushButton::clicked, this, [this, contactName,detailsDialog]() {
            DeleteContactButton(contactName);
            detailsDialog->close();
        });

        connect(editButton, &QPushButton::clicked, this, [this, contact, detailsDialog]() {
            EditContactWidget* editDialog = new EditContactWidget(contact, cntMng, this);
            editDialog->setAttribute(Qt::WA_DeleteOnClose);
            editDialog->show();

            connect(editDialog, &EditContactWidget::contactUpdated, this, &MainWindow::refreshContactList);
            detailsDialog->close(); // Close the details dialog immediately after opening the edit dialog
        });

        buttonsLayout->addWidget(editButton);
        buttonsLayout->addWidget(deleteButton);
        buttonsLayout->addWidget(closeButton);

        layout->addLayout(buttonsLayout) ;

        detailsDialog->setLayout(layout);
        detailsDialog->setWindowTitle("Contact Details");
        detailsDialog->exec();
    }
}

void MainWindow::DeleteContactButton(const QString &contactName){
    cntMng->DeleteContact(contactName);

    // Find and remove the item from the model
    for (int row = 0; row < MODEL->rowCount(); ++row) {
        QStandardItem* item = MODEL->item(row);
        if (item && item->text() == contactName) {
            MODEL->removeRow(row);
            break;
        }
    }

}


void MainWindow::refreshContactList() {
    MODEL->clear(); // Clear the existing list
    showContactList();
}
