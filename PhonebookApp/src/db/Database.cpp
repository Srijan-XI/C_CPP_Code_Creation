#include "Database.h"
#include <QSqlError>
#include <QSqlRecord>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

const QString Database::DATABASE_NAME = "phonebook.db";
const QString Database::CONNECTION_NAME = "PhonebookConnection";

Database::Database(QObject* parent)
    : QObject(parent)
    , m_isInitialized(false) {
}

Database::~Database() {
    close();
}

bool Database::initialize(const QString& databasePath) {
    if (m_isInitialized) {
        return true;
    }
    
    m_databasePath = databasePath.isEmpty() ? getDefaultDatabasePath() : databasePath;
    
    // Ensure directory exists
    QFileInfo fileInfo(m_databasePath);
    QDir().mkpath(fileInfo.absolutePath());
    
    m_database = QSqlDatabase::addDatabase("QSQLITE", CONNECTION_NAME);
    m_database.setDatabaseName(m_databasePath);
    
    if (!m_database.open()) {
        QString error = QString("Failed to open database: %1").arg(m_database.lastError().text());
        emit databaseError(error);
        qWarning() << error;
        return false;
    }
    
    if (!createTables()) {
        close();
        return false;
    }
    
    if (!executeMigrations()) {
        close();
        return false;
    }
    
    m_isInitialized = true;
    return true;
}

bool Database::isConnected() const {
    return m_database.isOpen() && m_isInitialized;
}

void Database::close() {
    if (m_database.isOpen()) {
        m_database.close();
    }
    QSqlDatabase::removeDatabase(CONNECTION_NAME);
    m_isInitialized = false;
}

bool Database::saveContact(const Contact& contact) {
    if (!isConnected()) {
        emit databaseError("Database is not connected");
        return false;
    }
    
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO contacts (name, phone, email) VALUES (?, ?, ?)");
    query.addBindValue(contact.getName());
    query.addBindValue(contact.getPhone());
    query.addBindValue(contact.getEmail());
    
    if (!query.exec()) {
        logError("saveContact", query);
        return false;
    }
    
    emit contactSaved(contact);
    return true;
}

bool Database::updateContact(const Contact& contact) {
    if (!isConnected()) {
        emit databaseError("Database is not connected");
        return false;
    }
    
    QSqlQuery query(m_database);
    query.prepare("UPDATE contacts SET name = ?, phone = ?, email = ? WHERE id = ?");
    query.addBindValue(contact.getName());
    query.addBindValue(contact.getPhone());
    query.addBindValue(contact.getEmail());
    query.addBindValue(contact.getId());
    
    if (!query.exec()) {
        logError("updateContact", query);
        return false;
    }
    
    if (query.numRowsAffected() == 0) {
        emit databaseError("Contact not found for update");
        return false;
    }
    
    emit contactUpdated(contact);
    return true;
}

bool Database::deleteContact(int contactId) {
    if (!isConnected()) {
        emit databaseError("Database is not connected");
        return false;
    }
    
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM contacts WHERE id = ?");
    query.addBindValue(contactId);
    
    if (!query.exec()) {
        logError("deleteContact", query);
        return false;
    }
    
    if (query.numRowsAffected() == 0) {
        emit databaseError("Contact not found for deletion");
        return false;
    }
    
    emit contactDeleted(contactId);
    return true;
}

Contact Database::getContact(int contactId) const {
    if (!isConnected()) {
        return Contact();
    }
    
    QSqlQuery query(m_database);
    query.prepare("SELECT id, name, phone, email FROM contacts WHERE id = ?");
    query.addBindValue(contactId);
    
    if (!query.exec()) {
        logError("getContact", query);
        return Contact();
    }
    
    if (query.next()) {
        Contact contact(query.value("name").toString(),
                       query.value("phone").toString(),
                       query.value("email").toString());
        contact.setId(query.value("id").toInt());
        return contact;
    }
    
    return Contact();
}

QList<Contact> Database::getAllContacts() const {
    QList<Contact> contacts;
    
    if (!isConnected()) {
        return contacts;
    }
    
    QSqlQuery query("SELECT id, name, phone, email FROM contacts ORDER BY name", m_database);
    
    if (!query.exec()) {
        logError("getAllContacts", query);
        return contacts;
    }
    
    while (query.next()) {
        Contact contact(query.value("name").toString(),
                       query.value("phone").toString(),
                       query.value("email").toString());
        contact.setId(query.value("id").toInt());
        contacts.append(contact);
    }
    
    return contacts;
}

QList<Contact> Database::searchContacts(const QString& searchQuery) const {
    QList<Contact> contacts;
    
    if (!isConnected() || searchQuery.isEmpty()) {
        return contacts;
    }
    
    QSqlQuery query(m_database);
    query.prepare("SELECT id, name, phone, email FROM contacts "
                  "WHERE name LIKE ? OR phone LIKE ? OR email LIKE ? "
                  "ORDER BY name");
    
    QString likePattern = QString("%%1%").arg(searchQuery);
    query.addBindValue(likePattern);
    query.addBindValue(likePattern);
    query.addBindValue(likePattern);
    
    if (!query.exec()) {
        logError("searchContacts", query);
        return contacts;
    }
    
    while (query.next()) {
        Contact contact(query.value("name").toString(),
                       query.value("phone").toString(),
                       query.value("email").toString());
        contact.setId(query.value("id").toInt());
        contacts.append(contact);
    }
    
    return contacts;
}

bool Database::clearAllContacts() {
    if (!isConnected()) {
        emit databaseError("Database is not connected");
        return false;
    }
    
    QSqlQuery query("DELETE FROM contacts", m_database);
    
    if (!query.exec()) {
        logError("clearAllContacts", query);
        return false;
    }
    
    return true;
}

int Database::getContactCount() const {
    if (!isConnected()) {
        return 0;
    }
    
    QSqlQuery query("SELECT COUNT(*) FROM contacts", m_database);
    
    if (!query.exec()) {
        logError("getContactCount", query);
        return 0;
    }
    
    if (query.next()) {
        return query.value(0).toInt();
    }
    
    return 0;
}

bool Database::executeQuery(const QString& queryString) {
    if (!isConnected()) {
        emit databaseError("Database is not connected");
        return false;
    }
    
    QSqlQuery query(queryString, m_database);
    
    if (!query.exec()) {
        logError("executeQuery", query);
        return false;
    }
    
    return true;
}

bool Database::createTables() {
    QSqlQuery query(m_database);
    
    QString createContactsTable = R"(
        CREATE TABLE IF NOT EXISTS contacts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            phone TEXT NOT NULL,
            email TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            updated_at DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createContactsTable)) {
        logError("createTables", query);
        return false;
    }
    
    // Create indexes for better search performance
    QString createNameIndex = "CREATE INDEX IF NOT EXISTS idx_contacts_name ON contacts (name)";
    if (!query.exec(createNameIndex)) {
        logError("createNameIndex", query);
        return false;
    }
    
    QString createPhoneIndex = "CREATE INDEX IF NOT EXISTS idx_contacts_phone ON contacts (phone)";
    if (!query.exec(createPhoneIndex)) {
        logError("createPhoneIndex", query);
        return false;
    }
    
    return true;
}

bool Database::executeMigrations() {
    // Check if migrations.sql file exists and execute it
    QString migrationsPath = QDir::currentPath() + "/src/db/migrations.sql";
    QFile migrationsFile(migrationsPath);
    
    if (!migrationsFile.exists()) {
        // No migrations file, that's okay
        return true;
    }
    
    if (!migrationsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open migrations file:" << migrationsPath;
        return true; // Not critical
    }
    
    QTextStream in(&migrationsFile);
    QString migrations = in.readAll();
    
    if (migrations.isEmpty()) {
        return true;
    }
    
    // Execute migrations (simple approach - split by semicolon)
    QStringList migrationQueries = migrations.split(';', Qt::SkipEmptyParts);
    
    for (const QString& migrationQuery : migrationQueries) {
        QString trimmedQuery = migrationQuery.trimmed();
        if (!trimmedQuery.isEmpty()) {
            if (!executeQuery(trimmedQuery)) {
                qWarning() << "Failed to execute migration:" << trimmedQuery;
                // Continue with other migrations
            }
        }
    }
    
    return true;
}

QString Database::getDefaultDatabasePath() const {
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    return dataPath + "/" + DATABASE_NAME;
}

void Database::logError(const QString& operation, const QSqlQuery& query) const {
    QString error = QString("%1 failed: %2").arg(operation).arg(query.lastError().text());
    emit const_cast<Database*>(this)->databaseError(error);
    qWarning() << error;
}
