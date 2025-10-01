#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

// Standalone Contact class without Qt dependencies
class Contact {
public:
    Contact() : m_id(s_nextId++), m_name(""), m_phone(""), m_email("") {}
    
    Contact(const std::string& name, const std::string& phone, const std::string& email = "")
        : m_id(s_nextId++), m_name(name), m_phone(phone), m_email(email) {}
    
    // Getters
    std::string getName() const { return m_name; }
    std::string getPhone() const { return m_phone; }
    std::string getEmail() const { return m_email; }
    int getId() const { return m_id; }
    
    // Setters
    void setName(const std::string& name) { m_name = name; }
    void setPhone(const std::string& phone) { m_phone = phone; }
    void setEmail(const std::string& email) { m_email = email; }
    
    // Operators for BST comparison
    bool operator<(const Contact& other) const {
        return m_name < other.m_name;
    }
    
    bool operator>(const Contact& other) const {
        return m_name > other.m_name;
    }
    
    bool operator==(const Contact& other) const {
        return m_name == other.m_name && m_phone == other.m_phone;
    }
    
    bool isValid() const {
        return !m_name.empty() && !m_phone.empty();
    }
    
private:
    int m_id;
    std::string m_name;
    std::string m_phone;
    std::string m_email;
    
    static int s_nextId;
};

int Contact::s_nextId = 1;

// Simple BST implementation for demo
template<typename T>
class BST {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<Node> root;
    
    void insertHelper(std::unique_ptr<Node>& node, const T& value) {
        if (!node) {
            node = std::make_unique<Node>(value);
            return;
        }
        
        if (value < node->data) {
            insertHelper(node->left, value);
        } else if (value > node->data) {
            insertHelper(node->right, value);
        }
    }
    
    void inorderHelper(Node* node, std::vector<T>& result) const {
        if (node) {
            inorderHelper(node->left.get(), result);
            result.push_back(node->data);
            inorderHelper(node->right.get(), result);
        }
    }
    
public:
    BST() : root(nullptr) {}
    
    void insert(const T& value) {
        insertHelper(root, value);
    }
    
    std::vector<T> inorderTraversal() const {
        std::vector<T> result;
        inorderHelper(root.get(), result);
        return result;
    }
    
    bool isEmpty() const {
        return root == nullptr;
    }
};

// Demo application
int main() {
    std::cout << "=== Modern Phonebook Console Demo ===" << std::endl;
    std::cout << "Core functionality demonstration without Qt GUI" << std::endl;
    std::cout << "=========================================" << std::endl << std::endl;
    
    // Create a BST to store contacts
    BST<Contact> contactTree;
    
    // Add some sample contacts
    std::cout << "Adding sample contacts..." << std::endl;
    contactTree.insert(Contact("Alice Johnson", "123-456-7890", "alice@example.com"));
    contactTree.insert(Contact("Bob Smith", "987-654-3210", "bob@example.com"));
    contactTree.insert(Contact("Charlie Brown", "555-1234", "charlie@example.com"));
    contactTree.insert(Contact("Diana Wilson", "444-5678", "diana@example.com"));
    contactTree.insert(Contact("Edward Davis", "333-9999", "edward@example.com"));
    
    // Display all contacts (automatically sorted by BST)
    std::cout << "\nContacts in alphabetical order (BST in-order traversal):" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    
    auto contacts = contactTree.inorderTraversal();
    for (size_t i = 0; i < contacts.size(); ++i) {
        const auto& contact = contacts[i];
        std::cout << (i + 1) << ". " << contact.getName() 
                  << " | " << contact.getPhone();
        if (!contact.getEmail().empty()) {
            std::cout << " | " << contact.getEmail();
        }
        std::cout << std::endl;
    }
    
    // Demonstrate search functionality
    std::cout << "\nSearch demonstration:" << std::endl;
    std::cout << "-------------------" << std::endl;
    
    std::string searchTerm = "Alice";
    std::cout << "Searching for contacts containing '" << searchTerm << "':" << std::endl;
    
    for (const auto& contact : contacts) {
        if (contact.getName().find(searchTerm) != std::string::npos ||
            contact.getPhone().find(searchTerm) != std::string::npos ||
            contact.getEmail().find(searchTerm) != std::string::npos) {
            std::cout << "Found: " << contact.getName() << " - " << contact.getPhone() << std::endl;
        }
    }
    
    // Statistics
    std::cout << "\nStatistics:" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "Total contacts: " << contacts.size() << std::endl;
    
    int withEmail = 0;
    for (const auto& contact : contacts) {
        if (!contact.getEmail().empty()) {
            withEmail++;
        }
    }
    std::cout << "Contacts with email: " << withEmail << std::endl;
    std::cout << "Contacts without email: " << (contacts.size() - withEmail) << std::endl;
    
    // Demonstrate contact validation
    std::cout << "\nContact validation demonstration:" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    Contact validContact("John Doe", "111-222-3333", "john@example.com");
    Contact invalidContact1("", "111-222-3333", "john@example.com");  // No name
    Contact invalidContact2("Jane Doe", "", "jane@example.com");      // No phone
    
    std::cout << "Valid contact: " << (validContact.isValid() ? "PASS" : "FAIL") << std::endl;
    std::cout << "Invalid contact (no name): " << (invalidContact1.isValid() ? "PASS" : "FAIL") << std::endl;
    std::cout << "Invalid contact (no phone): " << (invalidContact2.isValid() ? "PASS" : "FAIL") << std::endl;
    
    std::cout << "\n=== Demo Complete ===" << std::endl;
    std::cout << "This demonstrates the core BST and Contact functionality." << std::endl;
    std::cout << "The full Qt application includes:" << std::endl;
    std::cout << "- Modern GUI with tables and forms" << std::endl;
    std::cout << "- SQLite database integration" << std::endl;
    std::cout << "- Import/Export (JSON, CSV, XML)" << std::endl;
    std::cout << "- Advanced search and filtering" << std::endl;
    std::cout << "- Thread-safe operations" << std::endl;
    std::cout << "- Comprehensive unit tests" << std::endl;
    std::cout << "\nTo build the full application, install Qt6 and use the main CMakeLists.txt" << std::endl;
    
    return 0;
}