#include <gtest/gtest.h>
#include "core/BST.h"
#include "core/Contact.h"

class BSTTest : public ::testing::Test {
protected:
    void SetUp() override {
        bst = new BST<Contact>();
        
        // Create test contacts
        contact1 = Contact("Alice", "123-456-7890", "alice@example.com");
        contact2 = Contact("Bob", "987-654-3210", "bob@example.com");
        contact3 = Contact("Charlie", "555-1234", "charlie@example.com");
    }
    
    void TearDown() override {
        delete bst;
    }
    
    BST<Contact>* bst;
    Contact contact1, contact2, contact3;
};

TEST_F(BSTTest, EmptyTree) {
    EXPECT_TRUE(bst->isEmpty());
    EXPECT_EQ(bst->size(), 0);
}

TEST_F(BSTTest, InsertAndFind) {
    bst->insert(contact1);
    EXPECT_FALSE(bst->isEmpty());
    EXPECT_EQ(bst->size(), 1);
    EXPECT_TRUE(bst->contains(contact1));
    
    Contact* found = bst->find(contact1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getName(), contact1.getName());
}

TEST_F(BSTTest, MultipleInserts) {
    bst->insert(contact1);
    bst->insert(contact2);
    bst->insert(contact3);
    
    EXPECT_EQ(bst->size(), 3);
    EXPECT_TRUE(bst->contains(contact1));
    EXPECT_TRUE(bst->contains(contact2));
    EXPECT_TRUE(bst->contains(contact3));
}

TEST_F(BSTTest, InorderTraversal) {
    bst->insert(contact2); // Bob
    bst->insert(contact1); // Alice
    bst->insert(contact3); // Charlie
    
    QList<Contact> sorted = bst->inorderTraversal();
    EXPECT_EQ(sorted.size(), 3);
    
    // Should be sorted by name: Alice, Bob, Charlie
    EXPECT_EQ(sorted[0].getName(), "Alice");
    EXPECT_EQ(sorted[1].getName(), "Bob");
    EXPECT_EQ(sorted[2].getName(), "Charlie");
}

TEST_F(BSTTest, Remove) {
    bst->insert(contact1);
    bst->insert(contact2);
    bst->insert(contact3);
    
    EXPECT_TRUE(bst->remove(contact2));
    EXPECT_EQ(bst->size(), 2);
    EXPECT_FALSE(bst->contains(contact2));
    EXPECT_TRUE(bst->contains(contact1));
    EXPECT_TRUE(bst->contains(contact3));
    
    // Try to remove non-existent contact
    EXPECT_FALSE(bst->remove(contact2));
}

TEST_F(BSTTest, Clear) {
    bst->insert(contact1);
    bst->insert(contact2);
    bst->insert(contact3);
    
    bst->clear();
    EXPECT_TRUE(bst->isEmpty());
    EXPECT_EQ(bst->size(), 0);
}

TEST_F(BSTTest, Search) {
    bst->insert(contact1); // Alice
    bst->insert(contact2); // Bob
    bst->insert(contact3); // Charlie
    
    QList<Contact> results = bst->search("alice");
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].getName(), "Alice");
    
    results = bst->search("123");
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].getPhone(), "123-456-7890");
    
    results = bst->search("nonexistent");
    EXPECT_EQ(results.size(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
