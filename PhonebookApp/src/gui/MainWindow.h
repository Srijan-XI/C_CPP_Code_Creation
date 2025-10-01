#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>
#include <QHeaderView>
#include <QSplitter>
#include <QGroupBox>
#include <QFormLayout>
#include <QMessageBox>
#include "core/ContactManager.h"
#include "core/Contact.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;
    
protected:
    void closeEvent(QCloseEvent* event) override;
    
private slots:
    void onAddContact();
    void onEditContact();
    void onDeleteContact();
    void onSearchContacts();
    void onClearSearch();
    void onImportContacts();
    void onExportContacts();
    void onAbout();
    
    void onTableSelectionChanged();
    void onTableDoubleClicked(int row, int column);
    
    // ContactManager signals
    void onContactAdded(const Contact& contact);
    void onContactRemoved(const Contact& contact);
    void onContactUpdated(const Contact& oldContact, const Contact& newContact);
    void onContactsCleared();
    
private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void setupConnections();
    
    void refreshContactTable();
    void clearContactForm();
    void fillContactForm(const Contact& contact);
    Contact getContactFromForm() const;
    bool validateContactForm() const;
    
    void updateStatusBar();
    void showMessage(const QString& message, int timeout = 3000);
    
    // UI Components
    QWidget* m_centralWidget;
    QSplitter* m_mainSplitter;
    
    // Contact table
    QTableWidget* m_contactTable;
    QGroupBox* m_tableGroupBox;
    
    // Contact form
    QGroupBox* m_formGroupBox;
    QLineEdit* m_nameEdit;
    QLineEdit* m_phoneEdit;
    QLineEdit* m_emailEdit;
    QPushButton* m_addButton;
    QPushButton* m_editButton;
    QPushButton* m_deleteButton;
    QPushButton* m_clearButton;
    
    // Search
    QLineEdit* m_searchEdit;
    QPushButton* m_searchButton;
    QPushButton* m_clearSearchButton;
    
    // Menu and status
    QMenuBar* m_menuBar;
    QStatusBar* m_statusBar;
    QLabel* m_statusLabel;
    
    // Business logic
    ContactManager* m_contactManager;
    
    // State
    int m_currentSelectedRow;
    bool m_isEditing;
};

#endif // MAINWINDOW_H
