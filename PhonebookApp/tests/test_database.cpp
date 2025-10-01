#include <gtest/gtest.h>
#include <QTemporaryFile>
#include <QDir>
#include "db/Database.h"
#include "core/Contact.h"

class DatabaseTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Use a temporary file for testing
        tempFile = new QTemporaryFile();
        tempFile->open();
        tempFile->close();
        
        database = new Database();
        ASSERT_TRUE(database->initialize(tempFile->fileName()));
        
        // Create test contacts
        contact1 = Contact("Alice Johnson", "123-456-7890", "alice@example.com");
        contact2 = Contact("Bob Smith", "987-654-3210", "bob@example.com");
        contact3 = Contact("Charlie Brown", "555-1234", "charlie@example.com");
    }
    
    void TearDown() override {
        database->close();
        delete database;
        delete tempFile;
    }
    
    Database* database;
    QTemporaryFile* tempFile;
    Contact contact1, contact2, contact3;
};

TEST_F(DatabaseTest, Connection) {
    EXPECT_TRUE(database->isConnected());
}

TEST_F(DatabaseTest, SaveContact) {
    EXPECT_TRUE(database->saveContact(contact1));
    EXPECT_EQ(database->getContactCount(), 1);
}

TEST_F(DatabaseTest, GetAllContacts) {
    database->saveContact(contact1);
    database->saveContact(contact2);
    database->saveContact(contact3);
    
    QList<Contact> contacts = database->getAllContacts();
    EXPECT_EQ(contacts.size(), 3);
    
    // Should be sorted by name
    EXPECT_EQ(contacts[0].getName(), "Alice Johnson");
    EXPECT_EQ(contacts[1].getName(), "Bob Smith");
    EXPECT_EQ(contacts[2].getName(), "Charlie Brown");
}

TEST_F(DatabaseTest, SearchContacts) {
    database->saveContact(contact1);
    database->saveContact(contact2);
    database->saveContact(contact3);
    
    QList<Contact> results = database->searchContacts("Alice");
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].getName(), "Alice Johnson");
    
    results = database->searchContacts("123");
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].getPhone(), "123-456-7890");
    
    results = database->searchContacts("example.com");
    EXPECT_EQ(results.size(), 3); // All have example.com email
}

TEST_F(DatabaseTest, UpdateContact) {
    database->saveContact(contact1);
    QList<Contact> contacts = database->getAllContacts();
    ASSERT_EQ(contacts.size(), 1);
    
    Contact updatedContact = contacts[0];
    updatedContact.setEmail("alice.updated@example.com");
    
    EXPECT_TRUE(database->updateContact(updatedContact));
    
    Contact retrieved = database->getContact(updatedContact.getId());
    EXPECT_EQ(retrieved.getEmail(), "alice.updated@example.com");
}

TEST_F(DatabaseTest, DeleteContact) {
    database->saveContact(contact1);
    QList<Contact> contacts = database->getAllContacts();
    ASSERT_EQ(contacts.size(), 1);
    
    int contactId = contacts[0].getId();
    EXPECT_TRUE(database->deleteContact(contactId));
    EXPECT_EQ(database->getContactCount(), 0);
    
    // Try to delete non-existent contact
    EXPECT_FALSE(database->deleteContact(contactId));
}

TEST_F(DatabaseTest, ClearAllContacts) {
    database->saveContact(contact1);
    database->saveContact(contact2);
    database->saveContact(contact3);
    
    EXPECT_EQ(database->getContactCount(), 3);
    EXPECT_TRUE(database->clearAllContacts());
    EXPECT_EQ(database->getContactCount(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
