#include "FileHandler.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFileInfo>
#include <QDebug>

FileHandler::FileHandler(QObject* parent) : QObject(parent) {
}

bool FileHandler::exportContacts(const QList<Contact>& contacts, const QString& filePath, FileFormat format) {
    emit exportStarted();
    
    bool success = false;
    
    switch (format) {
        case JSON:
            success = exportToJson(contacts, filePath);
            break;
        case CSV:
            success = exportToCsv(contacts, filePath);
            break;
        case XML:
            success = exportToXml(contacts, filePath);
            break;
    }
    
    emit exportFinished(success);
    return success;
}

bool FileHandler::exportToJson(const QList<Contact>& contacts, const QString& filePath) {
    QJsonArray jsonArray;
    
    for (const Contact& contact : contacts) {
        QJsonObject contactObject;
        contactObject["id"] = contact.getId();
        contactObject["name"] = contact.getName();
        contactObject["phone"] = contact.getPhone();
        contactObject["email"] = contact.getEmail();
        jsonArray.append(contactObject);
    }
    
    QJsonDocument document(jsonArray);
    
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    file.write(document.toJson());
    return true;
}

bool FileHandler::exportToCsv(const QList<Contact>& contacts, const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    
    // Write header
    stream << "ID,Name,Phone,Email\n";
    
    // Write contacts
    for (const Contact& contact : contacts) {
        stream << contact.getId() << ","
               << escapeCsv(contact.getName()) << ","
               << escapeCsv(contact.getPhone()) << ","
               << escapeCsv(contact.getEmail()) << "\n";
    }
    
    return true;
}

bool FileHandler::exportToXml(const QList<Contact>& contacts, const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("contacts");
    
    for (const Contact& contact : contacts) {
        writer.writeStartElement("contact");
        writer.writeAttribute("id", QString::number(contact.getId()));
        
        writer.writeTextElement("name", contact.getName());
        writer.writeTextElement("phone", contact.getPhone());
        writer.writeTextElement("email", contact.getEmail());
        
        writer.writeEndElement(); // contact
    }
    
    writer.writeEndElement(); // contacts
    writer.writeEndDocument();
    
    return true;
}

QList<Contact> FileHandler::importContacts(const QString& filePath, FileFormat format) {
    emit importStarted();
    
    QList<Contact> contacts;
    
    switch (format) {
        case JSON:
            contacts = importFromJson(filePath);
            break;
        case CSV:
            contacts = importFromCsv(filePath);
            break;
        case XML:
            contacts = importFromXml(filePath);
            break;
    }
    
    emit importFinished(!contacts.isEmpty(), contacts.size());
    return contacts;
}

QList<Contact> FileHandler::importFromJson(const QString& filePath) {
    QList<Contact> contacts;
    
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file for reading:" << filePath;
        return contacts;
    }
    
    QByteArray data = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(data);
    
    if (!document.isArray()) {
        qWarning() << "Invalid JSON format - expected array";
        return contacts;
    }
    
    QJsonArray jsonArray = document.array();
    for (const QJsonValue& value : jsonArray) {
        if (!value.isObject()) {
            continue;
        }
        
        QJsonObject obj = value.toObject();
        Contact contact(obj["name"].toString(),
                       obj["phone"].toString(),
                       obj["email"].toString());
        
        if (obj.contains("id")) {
            contact.setId(obj["id"].toInt());
        }
        
        if (contact.isValid()) {
            contacts.append(contact);
        }
    }
    
    return contacts;
}

QList<Contact> FileHandler::importFromCsv(const QString& filePath) {
    QList<Contact> contacts;
    
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for reading:" << filePath;
        return contacts;
    }
    
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    
    // Skip header line
    if (!stream.atEnd()) {
        stream.readLine();
    }
    
    while (!stream.atEnd()) {
        QString line = stream.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }
        
        QStringList fields = line.split(',');
        if (fields.size() >= 3) {
            QString name = fields.size() > 1 ? fields[1].trimmed() : "";
            QString phone = fields.size() > 2 ? fields[2].trimmed() : "";
            QString email = fields.size() > 3 ? fields[3].trimmed() : "";
            
            // Remove quotes if present
            name = name.remove(QChar('"'));
            phone = phone.remove(QChar('"'));
            email = email.remove(QChar('"'));
            
            Contact contact(name, phone, email);
            
            // Set ID if provided
            if (!fields[0].isEmpty()) {
                bool ok;
                int id = fields[0].toInt(&ok);
                if (ok) {
                    contact.setId(id);
                }
            }
            
            if (contact.isValid()) {
                contacts.append(contact);
            }
        }
    }
    
    return contacts;
}

QList<Contact> FileHandler::importFromXml(const QString& filePath) {
    QList<Contact> contacts;
    
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file for reading:" << filePath;
        return contacts;
    }
    
    QXmlStreamReader reader(&file);
    
    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        
        if (token == QXmlStreamReader::StartElement && reader.name() == "contact") {
            QString name, phone, email;
            int id = 0;
            
            // Read ID attribute
            if (reader.attributes().hasAttribute("id")) {
                id = reader.attributes().value("id").toInt();
            }
            
            // Read contact elements
            while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "contact")) {
                if (reader.tokenType() == QXmlStreamReader::StartElement) {
                    if (reader.name() == "name") {
                        name = reader.readElementText();
                    } else if (reader.name() == "phone") {
                        phone = reader.readElementText();
                    } else if (reader.name() == "email") {
                        email = reader.readElementText();
                    }
                }
                reader.readNext();
            }
            
            Contact contact(name, phone, email);
            if (id > 0) {
                contact.setId(id);
            }
            
            if (contact.isValid()) {
                contacts.append(contact);
            }
        }
    }
    
    if (reader.hasError()) {
        qWarning() << "XML parsing error:" << reader.errorString();
        return QList<Contact>();
    }
    
    return contacts;
}

FileHandler::FileFormat FileHandler::detectFileFormat(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    QString extension = fileInfo.suffix().toLower();
    
    if (extension == "json") {
        return JSON;
    } else if (extension == "csv") {
        return CSV;
    } else if (extension == "xml") {
        return XML;
    }
    
    return JSON; // Default
}

QString FileHandler::getFileExtension(FileFormat format) {
    switch (format) {
        case JSON: return "json";
        case CSV: return "csv";
        case XML: return "xml";
        default: return "json";
    }
}

QString FileHandler::getFileFilter(FileFormat format) {
    switch (format) {
        case JSON: return "JSON Files (*.json)";
        case CSV: return "CSV Files (*.csv)";
        case XML: return "XML Files (*.xml)";
        default: return "JSON Files (*.json)";
    }
}

QString FileHandler::escapeHtml(const QString& text) const {
    QString escaped = text;
    escaped.replace("&", "&amp;");
    escaped.replace("<", "&lt;");
    escaped.replace(">", "&gt;");
    escaped.replace("\"", "&quot;");
    escaped.replace("'", "&#39;");
    return escaped;
}

QString FileHandler::escapeCsv(const QString& text) const {
    if (text.contains(',') || text.contains('"') || text.contains('\n')) {
        QString escaped = text;
        escaped.replace("\"", "\"\"");
        return "\"" + escaped + "\"";
    }
    return text;
}
