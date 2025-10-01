#include "ContactManager.h"
#include <QMutexLocker>
#include <QDebug>

ContactManager::ContactManager(QObject* parent) : QObject(parent) {
}

bool ContactManager::addContact(const Contact& contact) {
    if (!contact.isValid()) {
        qWarning() << "Cannot add invalid contact";
        return false;
    }
    
    QMutexLocker locker(&m_mutex);
    
    if (isContactDuplicate(contact)) {
        qWarning() << "Contact already exists:" << contact.getName() << contact.getPhone();
        return false;
    }
    
    m_contacts.insert(contact);
    emit contactAdded(contact);
    return true;
}

bool ContactManager::removeContact(const Contact& contact) {
    QMutexLocker locker(&m_mutex);
    
    if (m_contacts.remove(contact)) {
        emit contactRemoved(contact);
        return true;
    }
    
    return false;
}

bool ContactManager::updateContact(const Contact& oldContact, const Contact& newContact) {
    if (!newContact.isValid()) {
        qWarning() << "Cannot update to invalid contact";
        return false;
    }
    
    QMutexLocker locker(&m_mutex);
    
    // Check if new contact would create a duplicate (excluding the old one)
    if (!(oldContact == newContact) && isContactDuplicate(newContact)) {
        qWarning() << "Updated contact would create duplicate";
        return false;
    }
    
    if (m_contacts.remove(oldContact)) {
        m_contacts.insert(newContact);
        emit contactUpdated(oldContact, newContact);
        return true;
    }
    
    return false;
}

QList<Contact> ContactManager::getAllContacts() const {
    QMutexLocker locker(&m_mutex);
    return m_contacts.inorderTraversal();
}

QList<Contact> ContactManager::searchContacts(const QString& query) const {
    if (query.isEmpty()) {
        return getAllContacts();
    }
    
    QMutexLocker locker(&m_mutex);
    return m_contacts.search(query);
}

Contact* ContactManager::findContact(const QString& name, const QString& phone) {
    Contact searchContact(name, phone);
    QMutexLocker locker(&m_mutex);
    return m_contacts.find(searchContact);
}

const Contact* ContactManager::findContact(const QString& name, const QString& phone) const {
    Contact searchContact(name, phone);
    QMutexLocker locker(&m_mutex);
    return m_contacts.find(searchContact);
}

void ContactManager::clearAllContacts() {
    QMutexLocker locker(&m_mutex);
    m_contacts.clear();
    emit contactsCleared();
}

int ContactManager::getContactCount() const {
    QMutexLocker locker(&m_mutex);
    return static_cast<int>(m_contacts.size());
}

bool ContactManager::isEmpty() const {
    QMutexLocker locker(&m_mutex);
    return m_contacts.isEmpty();
}

QList<Contact> ContactManager::getContactsForExport() const {
    return getAllContacts();
}

bool ContactManager::importContacts(const QList<Contact>& contacts) {
    int successCount = 0;
    
    for (const Contact& contact : contacts) {
        if (addContact(contact)) {
            successCount++;
        }
    }
    
    return successCount > 0;
}

void ContactManager::sortContactsByName() {
    // BST automatically keeps contacts sorted by name
    // This method exists for interface compatibility
    emit contactsCleared(); // Trigger UI refresh
}

void ContactManager::sortContactsByPhone() {
    QMutexLocker locker(&m_mutex);
    QList<Contact> contacts = m_contacts.inorderTraversal();
    
    // Sort by phone number
    std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return a.getPhone() < b.getPhone();
    });
    
    // This is for display purposes only - the BST structure remains unchanged
    // In a real implementation, you might want to emit a sorted list
}

bool ContactManager::isContactDuplicate(const Contact& contact) const {
    // Check for exact match (name and phone)
    return m_contacts.contains(contact);
}
