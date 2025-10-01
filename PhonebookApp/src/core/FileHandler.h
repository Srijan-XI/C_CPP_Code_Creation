#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QString>
#include <QList>
#include "Contact.h"

class FileHandler : public QObject {
    Q_OBJECT
    
public:
    enum FileFormat {
        JSON,
        CSV,
        XML
    };
    
    explicit FileHandler(QObject* parent = nullptr);
    ~FileHandler() = default;
    
    // Export operations
    bool exportContacts(const QList<Contact>& contacts, const QString& filePath, FileFormat format = JSON);
    bool exportToJson(const QList<Contact>& contacts, const QString& filePath);
    bool exportToCsv(const QList<Contact>& contacts, const QString& filePath);
    bool exportToXml(const QList<Contact>& contacts, const QString& filePath);
    
    // Import operations
    QList<Contact> importContacts(const QString& filePath, FileFormat format = JSON);
    QList<Contact> importFromJson(const QString& filePath);
    QList<Contact> importFromCsv(const QString& filePath);
    QList<Contact> importFromXml(const QString& filePath);
    
    // Utility methods
    static FileFormat detectFileFormat(const QString& filePath);
    static QString getFileExtension(FileFormat format);
    static QString getFileFilter(FileFormat format);
    
signals:
    void exportStarted();
    void exportFinished(bool success);
    void importStarted();
    void importFinished(bool success, int contactCount);
    
private:
    QString escapeHtml(const QString& text) const;
    QString escapeCsv(const QString& text) const;
};

#endif // FILEHANDLER_H
