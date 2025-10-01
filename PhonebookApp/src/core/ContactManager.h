#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include "Contact.h"
#include "BST.h"
#include <QObject>
#include <QList>
#include <memory>
#include <QMutex>

class ContactManager : public QObject {
    Q_OBJECT
    
public:
    explicit ContactManager(QObject* parent = nullptr);
    ~ContactManager() = default;
    
    // Contact management
    bool addContact(const Contact& contact);
    bool removeContact(const Contact& contact);
    bool updateContact(const Contact& oldContact, const Contact& newContact);
    
    // Search and retrieval
    QList<Contact> getAllContacts() const;
    QList<Contact> searchContacts(const QString& query) const;
    Contact* findContact(const QString& name, const QString& phone);
    const Contact* findContact(const QString& name, const QString& phone) const;
    
    // Bulk operations
    void clearAllContacts();
    int getContactCount() const;
    bool isEmpty() const;
    
    // Import/Export support
    QList<Contact> getContactsForExport() const;
    bool importContacts(const QList<Contact>& contacts);
    
public slots:
    void sortContactsByName();
    void sortContactsByPhone();
    
signals:
    void contactAdded(const Contact& contact);
    void contactRemoved(const Contact& contact);
    void contactUpdated(const Contact& oldContact, const Contact& newContact);
    void contactsCleared();
    
private:
    BST<Contact> m_contacts;
    mutable QMutex m_mutex;  // Thread safety
    
    bool isContactDuplicate(const Contact& contact) const;
};

#endif // CONTACTMANAGER_H
