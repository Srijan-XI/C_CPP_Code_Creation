#include <gtest/gtest.h>
#include <QTemporaryFile>
#include <QJsonDocument>
#include <QJsonArray>
#include "core/FileHandler.h"
#include "core/Contact.h"

class FileHandlerTest : public ::testing::Test {
protected:
    void SetUp() override {
        fileHandler = new FileHandler();
        
        // Create test contacts
        contacts.append(Contact("Alice Johnson", "123-456-7890", "alice@example.com"));
        contacts.append(Contact("Bob Smith", "987-654-3210", "bob@example.com"));
        contacts.append(Contact("Charlie Brown", "555-1234", "charlie@example.com"));
    }
    
    void TearDown() override {
        delete fileHandler;
    }
    
    FileHandler* fileHandler;
    QList<Contact> contacts;
};

TEST_F(FileHandlerTest, ExportToJson) {
    QTemporaryFile tempFile;
    tempFile.open();
    QString fileName = tempFile.fileName();
    tempFile.close();
    
    EXPECT_TRUE(fileHandler->exportToJson(contacts, fileName));
    
    // Verify the file was created and has content
    QFile file(fileName);
    ASSERT_TRUE(file.open(QIODevice::ReadOnly));
    
    QByteArray data = file.readAll();
    EXPECT_FALSE(data.isEmpty());
    
    // Verify JSON structure
    QJsonDocument doc = QJsonDocument::fromJson(data);
    ASSERT_TRUE(doc.isArray());
    
    QJsonArray array = doc.array();
    EXPECT_EQ(array.size(), 3);
}

TEST_F(FileHandlerTest, ExportToCsv) {
    QTemporaryFile tempFile;
    tempFile.open();
    QString fileName = tempFile.fileName();
    tempFile.close();
    
    EXPECT_TRUE(fileHandler->exportToCsv(contacts, fileName));
    
    // Verify the file was created and has content
    QFile file(fileName);
    ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
    
    QTextStream stream(&file);
    QString firstLine = stream.readLine();
    EXPECT_EQ(firstLine, "ID,Name,Phone,Email");
    
    QString secondLine = stream.readLine();
    EXPECT_TRUE(secondLine.contains("Alice Johnson"));
}

TEST_F(FileHandlerTest, ExportToXml) {
    QTemporaryFile tempFile;
    tempFile.open();
    QString fileName = tempFile.fileName();
    tempFile.close();
    
    EXPECT_TRUE(fileHandler->exportToXml(contacts, fileName));
    
    // Verify the file was created and has content
    QFile file(fileName);
    ASSERT_TRUE(file.open(QIODevice::ReadOnly));
    
    QString data = file.readAll();
    EXPECT_TRUE(data.contains("<contacts>"));
    EXPECT_TRUE(data.contains("<contact"));
    EXPECT_TRUE(data.contains("Alice Johnson"));
}

TEST_F(FileHandlerTest, ImportFromJson) {
    // First export to create a test file
    QTemporaryFile tempFile;
    tempFile.open();
    QString fileName = tempFile.fileName();
    tempFile.close();
    
    ASSERT_TRUE(fileHandler->exportToJson(contacts, fileName));
    
    // Now import and verify
    QList<Contact> importedContacts = fileHandler->importFromJson(fileName);
    EXPECT_EQ(importedContacts.size(), 3);
    
    EXPECT_EQ(importedContacts[0].getName(), "Alice Johnson");
    EXPECT_EQ(importedContacts[1].getName(), "Bob Smith");
    EXPECT_EQ(importedContacts[2].getName(), "Charlie Brown");
}

TEST_F(FileHandlerTest, ImportFromCsv) {
    // First export to create a test file
    QTemporaryFile tempFile;
    tempFile.open();
    QString fileName = tempFile.fileName();
    tempFile.close();
    
    ASSERT_TRUE(fileHandler->exportToCsv(contacts, fileName));
    
    // Now import and verify
    QList<Contact> importedContacts = fileHandler->importFromCsv(fileName);
    EXPECT_EQ(importedContacts.size(), 3);
    
    EXPECT_EQ(importedContacts[0].getName(), "Alice Johnson");
    EXPECT_EQ(importedContacts[1].getName(), "Bob Smith");
    EXPECT_EQ(importedContacts[2].getName(), "Charlie Brown");
}

TEST_F(FileHandlerTest, DetectFileFormat) {
    EXPECT_EQ(FileHandler::detectFileFormat("test.json"), FileHandler::JSON);
    EXPECT_EQ(FileHandler::detectFileFormat("test.csv"), FileHandler::CSV);
    EXPECT_EQ(FileHandler::detectFileFormat("test.xml"), FileHandler::XML);
    EXPECT_EQ(FileHandler::detectFileFormat("test.unknown"), FileHandler::JSON); // Default
}

TEST_F(FileHandlerTest, GetFileExtension) {
    EXPECT_EQ(FileHandler::getFileExtension(FileHandler::JSON), "json");
    EXPECT_EQ(FileHandler::getFileExtension(FileHandler::CSV), "csv");
    EXPECT_EQ(FileHandler::getFileExtension(FileHandler::XML), "xml");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
