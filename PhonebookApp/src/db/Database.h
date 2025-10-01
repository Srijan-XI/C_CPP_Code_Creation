#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QList>
#include "core/Contact.h"

class Database : public QObject {
    Q_OBJECT
    
public:
    explicit Database(QObject* parent = nullptr);
    ~Database();
    
    // Database management
    bool initialize(const QString& databasePath = "");
    bool isConnected() const;
    void close();
    
    // Contact operations
    bool saveContact(const Contact& contact);
    bool updateContact(const Contact& contact);
    bool deleteContact(int contactId);
    Contact getContact(int contactId) const;
    QList<Contact> getAllContacts() const;
    QList<Contact> searchContacts(const QString& query) const;
    
    // Utility methods
    bool clearAllContacts();
    int getContactCount() const;
    bool executeQuery(const QString& query);
    
signals:
    void databaseError(const QString& error);
    void contactSaved(const Contact& contact);
    void contactUpdated(const Contact& contact);
    void contactDeleted(int contactId);
    
private:
    bool createTables();
    bool executeMigrations();
    QString getDefaultDatabasePath() const;
    void logError(const QString& operation, const QSqlQuery& query) const;
    
    QSqlDatabase m_database;
    QString m_databasePath;
    bool m_isInitialized;
    
    static const QString DATABASE_NAME;
    static const QString CONNECTION_NAME;
};

#endif // DATABASE_H
