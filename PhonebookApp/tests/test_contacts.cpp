#include <gtest/gtest.h>
#include "core/Contact.h"

class ContactTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test data
    }
    
    void TearDown() override {
        // Clean up
    }
};

TEST_F(ContactTest, DefaultConstructor) {
    Contact contact;
    EXPECT_TRUE(contact.getName().isEmpty());
    EXPECT_TRUE(contact.getPhone().isEmpty());
    EXPECT_TRUE(contact.getEmail().isEmpty());
    EXPECT_GT(contact.getId(), 0);
}

TEST_F(ContactTest, ParameterizedConstructor) {
    Contact contact("John Doe", "123-456-7890", "john@example.com");
    EXPECT_EQ(contact.getName(), "John Doe");
    EXPECT_EQ(contact.getPhone(), "123-456-7890");
    EXPECT_EQ(contact.getEmail(), "john@example.com");
    EXPECT_GT(contact.getId(), 0);
}

TEST_F(ContactTest, Validation) {
    Contact validContact("John Doe", "123-456-7890", "john@example.com");
    EXPECT_TRUE(validContact.isValid());
    
    Contact invalidContactNoName("", "123-456-7890", "john@example.com");
    EXPECT_FALSE(invalidContactNoName.isValid());
    
    Contact invalidContactNoPhone("John Doe", "", "john@example.com");
    EXPECT_FALSE(invalidContactNoPhone.isValid());
    
    Contact invalidEmail("John Doe", "123-456-7890", "invalid-email");
    EXPECT_FALSE(invalidEmail.isValid());
}

TEST_F(ContactTest, Comparison) {
    Contact contact1("Alice", "123-456-7890");
    Contact contact2("Bob", "987-654-3210");
    Contact contact3("Alice", "111-222-3333");
    
    EXPECT_TRUE(contact1 < contact2);
    EXPECT_FALSE(contact2 < contact1);
    EXPECT_FALSE(contact1 == contact3); // Different phone numbers
}

TEST_F(ContactTest, SettersAndGetters) {
    Contact contact;
    
    contact.setName("Jane Doe");
    contact.setPhone("555-1234");
    contact.setEmail("jane@example.com");
    contact.setId(42);
    
    EXPECT_EQ(contact.getName(), "Jane Doe");
    EXPECT_EQ(contact.getPhone(), "555-1234");
    EXPECT_EQ(contact.getEmail(), "jane@example.com");
    EXPECT_EQ(contact.getId(), 42);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
