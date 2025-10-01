#include "MainWindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QHeaderView>
#include <QSplitter>
#include <QGroupBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainSplitter(nullptr)
    , m_contactTable(nullptr)
    , m_tableGroupBox(nullptr)
    , m_formGroupBox(nullptr)
    , m_nameEdit(nullptr)
    , m_phoneEdit(nullptr)
    , m_emailEdit(nullptr)
    , m_addButton(nullptr)
    , m_editButton(nullptr)
    , m_deleteButton(nullptr)
    , m_clearButton(nullptr)
    , m_searchEdit(nullptr)
    , m_searchButton(nullptr)
    , m_clearSearchButton(nullptr)
    , m_menuBar(nullptr)
    , m_statusBar(nullptr)
    , m_statusLabel(nullptr)
    , m_contactManager(nullptr)
    , m_currentSelectedRow(-1)
    , m_isEditing(false) {
    
    m_contactManager = new ContactManager(this);
    setupUI();
    setupMenuBar();
    setupStatusBar();
    setupConnections();
    
    setWindowTitle("Modern Phonebook");
    setMinimumSize(800, 600);
    resize(1000, 700);
    
    updateStatusBar();
}

void MainWindow::setupUI() {
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    // Main splitter
    m_mainSplitter = new QSplitter(Qt::Horizontal, this);
    
    // Left side - Contact table
    setupContactTable();
    
    // Right side - Contact form
    setupContactForm();
    
    // Search bar
    setupSearchBar();
    
    // Layout
    QVBoxLayout* mainLayout = new QVBoxLayout(m_centralWidget);
    
    // Search bar at the top
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchLayout->addWidget(new QLabel("Search:"));
    searchLayout->addWidget(m_searchEdit);
    searchLayout->addWidget(m_searchButton);
    searchLayout->addWidget(m_clearSearchButton);
    searchLayout->addStretch();
    
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(m_mainSplitter);
    
    // Set splitter proportions
    m_mainSplitter->setSizes({600, 400});
}

void MainWindow::setupContactTable() {
    m_tableGroupBox = new QGroupBox("Contacts", this);
    m_contactTable = new QTableWidget(0, 3, this);
    
    QStringList headers;
    headers << "Name" << "Phone" << "Email";
    m_contactTable->setHorizontalHeaderLabels(headers);
    
    // Table properties
    m_contactTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_contactTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_contactTable->setAlternatingRowColors(true);
    m_contactTable->setSortingEnabled(true);
    m_contactTable->horizontalHeader()->setStretchLastSection(true);
    m_contactTable->verticalHeader()->setVisible(false);
    
    // Layout
    QVBoxLayout* tableLayout = new QVBoxLayout(m_tableGroupBox);
    tableLayout->addWidget(m_contactTable);
    
    m_mainSplitter->addWidget(m_tableGroupBox);
}

void MainWindow::setupContactForm() {
    m_formGroupBox = new QGroupBox("Contact Details", this);
    
    // Form fields
    m_nameEdit = new QLineEdit(this);
    m_phoneEdit = new QLineEdit(this);
    m_emailEdit = new QLineEdit(this);
    
    m_nameEdit->setPlaceholderText("Enter full name");
    m_phoneEdit->setPlaceholderText("Enter phone number");
    m_emailEdit->setPlaceholderText("Enter email (optional)");
    
    // Buttons
    m_addButton = new QPushButton("Add Contact", this);
    m_editButton = new QPushButton("Edit Contact", this);
    m_deleteButton = new QPushButton("Delete Contact", this);
    m_clearButton = new QPushButton("Clear Form", this);
    
    m_editButton->setEnabled(false);
    m_deleteButton->setEnabled(false);
    
    // Layout
    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow("Name:", m_nameEdit);
    formLayout->addRow("Phone:", m_phoneEdit);
    formLayout->addRow("Email:", m_emailEdit);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_editButton);
    buttonLayout->addWidget(m_deleteButton);
    buttonLayout->addWidget(m_clearButton);
    buttonLayout->addStretch();
    
    QVBoxLayout* formMainLayout = new QVBoxLayout(m_formGroupBox);
    formMainLayout->addLayout(formLayout);
    formMainLayout->addLayout(buttonLayout);
    formMainLayout->addStretch();
    
    m_mainSplitter->addWidget(m_formGroupBox);
}

void MainWindow::setupSearchBar() {
    m_searchEdit = new QLineEdit(this);
    m_searchButton = new QPushButton("Search", this);
    m_clearSearchButton = new QPushButton("Clear", this);
    
    m_searchEdit->setPlaceholderText("Search contacts by name, phone, or email");
}

void MainWindow::setupMenuBar() {
    // File menu
    QMenu* fileMenu = menuBar()->addMenu("&File");
    
    QAction* importAction = fileMenu->addAction("&Import Contacts...");
    QAction* exportAction = fileMenu->addAction("&Export Contacts...");
    fileMenu->addSeparator();
    QAction* exitAction = fileMenu->addAction("E&xit");
    
    connect(importAction, &QAction::triggered, this, &MainWindow::onImportContacts);
    connect(exportAction, &QAction::triggered, this, &MainWindow::onExportContacts);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    
    // Help menu
    QMenu* helpMenu = menuBar()->addMenu("&Help");
    QAction* aboutAction = helpMenu->addAction("&About");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
}

void MainWindow::setupStatusBar() {
    m_statusLabel = new QLabel(this);
    statusBar()->addWidget(m_statusLabel);
}

void MainWindow::setupConnections() {
    // Form buttons
    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::onAddContact);
    connect(m_editButton, &QPushButton::clicked, this, &MainWindow::onEditContact);
    connect(m_deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteContact);
    connect(m_clearButton, &QPushButton::clicked, this, &MainWindow::clearContactForm);
    
    // Search
    connect(m_searchButton, &QPushButton::clicked, this, &MainWindow::onSearchContacts);
    connect(m_clearSearchButton, &QPushButton::clicked, this, &MainWindow::onClearSearch);
    connect(m_searchEdit, &QLineEdit::returnPressed, this, &MainWindow::onSearchContacts);
    
    // Table
    connect(m_contactTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::onTableSelectionChanged);
    connect(m_contactTable, &QTableWidget::cellDoubleClicked, this, &MainWindow::onTableDoubleClicked);
    
    // ContactManager signals
    connect(m_contactManager, &ContactManager::contactAdded, this, &MainWindow::onContactAdded);
    connect(m_contactManager, &ContactManager::contactRemoved, this, &MainWindow::onContactRemoved);
    connect(m_contactManager, &ContactManager::contactUpdated, this, &MainWindow::onContactUpdated);
    connect(m_contactManager, &ContactManager::contactsCleared, this, &MainWindow::onContactsCleared);
}

void MainWindow::onAddContact() {
    if (!validateContactForm()) {
        return;
    }
    
    Contact contact = getContactFromForm();
    if (m_contactManager->addContact(contact)) {
        clearContactForm();
        showMessage("Contact added successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to add contact. Contact may already exist.");
    }
}

void MainWindow::onEditContact() {
    if (m_currentSelectedRow < 0) {
        return;
    }
    
    if (!validateContactForm()) {
        return;
    }
    
    // Get original contact from table
    QString originalName = m_contactTable->item(m_currentSelectedRow, 0)->text();
    QString originalPhone = m_contactTable->item(m_currentSelectedRow, 1)->text();
    Contact originalContact(originalName, originalPhone);
    
    Contact newContact = getContactFromForm();
    
    if (m_contactManager->updateContact(originalContact, newContact)) {
        clearContactForm();
        m_isEditing = false;
        m_addButton->setText("Add Contact");
        showMessage("Contact updated successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to update contact.");
    }
}

void MainWindow::onDeleteContact() {
    if (m_currentSelectedRow < 0) {
        return;
    }
    
    QString name = m_contactTable->item(m_currentSelectedRow, 0)->text();
    QString phone = m_contactTable->item(m_currentSelectedRow, 1)->text();
    
    int ret = QMessageBox::question(this, "Confirm Delete", 
                                   QString("Are you sure you want to delete contact '%1'?").arg(name),
                                   QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        Contact contact(name, phone);
        if (m_contactManager->removeContact(contact)) {
            clearContactForm();
            showMessage("Contact deleted successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete contact.");
        }
    }
}

void MainWindow::onSearchContacts() {
    QString query = m_searchEdit->text();
    QList<Contact> results = m_contactManager->searchContacts(query);
    
    refreshContactTable();
    
    if (!query.isEmpty()) {
        showMessage(QString("Found %1 contact(s) matching '%2'").arg(results.size()).arg(query));
    }
}

void MainWindow::onClearSearch() {
    m_searchEdit->clear();
    refreshContactTable();
    showMessage("Search cleared");
}

void MainWindow::onImportContacts() {
    // Placeholder for import functionality
    QMessageBox::information(this, "Import", "Import functionality not yet implemented.");
}

void MainWindow::onExportContacts() {
    // Placeholder for export functionality
    QMessageBox::information(this, "Export", "Export functionality not yet implemented.");
}

void MainWindow::onAbout() {
    QMessageBox::about(this, "About Modern Phonebook", 
                      "Modern Phonebook v1.0\n\n"
                      "A Qt-based phonebook application with:\n"
                      "• Binary Search Tree data structure\n"
                      "• Fast search and sorting\n"
                      "• Modern user interface\n\n"
                      "Built with Qt6 and C++20");
}

void MainWindow::onTableSelectionChanged() {
    QList<QTableWidgetItem*> selectedItems = m_contactTable->selectedItems();
    
    if (selectedItems.isEmpty()) {
        m_currentSelectedRow = -1;
        m_editButton->setEnabled(false);
        m_deleteButton->setEnabled(false);
        clearContactForm();
    } else {
        m_currentSelectedRow = selectedItems.first()->row();
        m_editButton->setEnabled(true);
        m_deleteButton->setEnabled(true);
        
        // Fill form with selected contact
        QString name = m_contactTable->item(m_currentSelectedRow, 0)->text();
        QString phone = m_contactTable->item(m_currentSelectedRow, 1)->text();
        QString email = m_contactTable->item(m_currentSelectedRow, 2)->text();
        
        Contact contact(name, phone, email);
        fillContactForm(contact);
    }
}

void MainWindow::onTableDoubleClicked(int row, int column) {
    Q_UNUSED(column)
    m_currentSelectedRow = row;
    
    // Switch to edit mode
    m_isEditing = true;
    m_addButton->setText("Update Contact");
    
    onTableSelectionChanged(); // Fill the form
}

void MainWindow::onContactAdded(const Contact& contact) {
    Q_UNUSED(contact)
    refreshContactTable();
    updateStatusBar();
}

void MainWindow::onContactRemoved(const Contact& contact) {
    Q_UNUSED(contact)
    refreshContactTable();
    updateStatusBar();
}

void MainWindow::onContactUpdated(const Contact& oldContact, const Contact& newContact) {
    Q_UNUSED(oldContact)
    Q_UNUSED(newContact)
    refreshContactTable();
    updateStatusBar();
}

void MainWindow::onContactsCleared() {
    refreshContactTable();
    updateStatusBar();
}

void MainWindow::refreshContactTable() {
    QString searchQuery = m_searchEdit->text();
    QList<Contact> contacts;
    
    if (searchQuery.isEmpty()) {
        contacts = m_contactManager->getAllContacts();
    } else {
        contacts = m_contactManager->searchContacts(searchQuery);
    }
    
    m_contactTable->setRowCount(contacts.size());
    
    for (int i = 0; i < contacts.size(); ++i) {
        const Contact& contact = contacts[i];
        
        m_contactTable->setItem(i, 0, new QTableWidgetItem(contact.getName()));
        m_contactTable->setItem(i, 1, new QTableWidgetItem(contact.getPhone()));
        m_contactTable->setItem(i, 2, new QTableWidgetItem(contact.getEmail()));
    }
    
    // Adjust column widths
    m_contactTable->resizeColumnsToContents();
}

void MainWindow::clearContactForm() {
    m_nameEdit->clear();
    m_phoneEdit->clear();
    m_emailEdit->clear();
    
    m_isEditing = false;
    m_addButton->setText("Add Contact");
    m_currentSelectedRow = -1;
    m_editButton->setEnabled(false);
    m_deleteButton->setEnabled(false);
}

void MainWindow::fillContactForm(const Contact& contact) {
    m_nameEdit->setText(contact.getName());
    m_phoneEdit->setText(contact.getPhone());
    m_emailEdit->setText(contact.getEmail());
}

Contact MainWindow::getContactFromForm() const {
    return Contact(m_nameEdit->text().trimmed(),
                  m_phoneEdit->text().trimmed(),
                  m_emailEdit->text().trimmed());
}

bool MainWindow::validateContactForm() const {
    if (m_nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(const_cast<MainWindow*>(this), "Validation Error", "Name is required.");
        m_nameEdit->setFocus();
        return false;
    }
    
    if (m_phoneEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(const_cast<MainWindow*>(this), "Validation Error", "Phone number is required.");
        m_phoneEdit->setFocus();
        return false;
    }
    
    Contact testContact = getContactFromForm();
    if (!testContact.isValid()) {
        QMessageBox::warning(const_cast<MainWindow*>(this), "Validation Error", 
                           "Please check the format of phone number and email address.");
        return false;
    }
    
    return true;
}

void MainWindow::updateStatusBar() {
    int contactCount = m_contactManager->getContactCount();
    m_statusLabel->setText(QString("Total contacts: %1").arg(contactCount));
}

void MainWindow::showMessage(const QString& message, int timeout) {
    statusBar()->showMessage(message, timeout);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    int contactCount = m_contactManager->getContactCount();
    
    if (contactCount > 0) {
        int ret = QMessageBox::question(this, "Exit Confirmation",
                                       QString("You have %1 contact(s). Are you sure you want to exit?").arg(contactCount),
                                       QMessageBox::Yes | QMessageBox::No);
        
        if (ret == QMessageBox::No) {
            event->ignore();
            return;
        }
    }
    
    event->accept();
}
