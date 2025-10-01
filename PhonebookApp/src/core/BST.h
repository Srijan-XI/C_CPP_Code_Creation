#ifndef BST_H
#define BST_H

#include "Contact.h"
#include <QList>
#include <memory>

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
    
    void insertHelper(std::unique_ptr<Node>& node, const T& value);
    bool removeHelper(std::unique_ptr<Node>& node, const T& value);
    Node* findHelper(Node* node, const T& value) const;
    void inorderHelper(Node* node, QList<T>& result) const;
    void clearHelper(std::unique_ptr<Node>& node);
    
public:
    BST();
    ~BST() = default;
    
    void insert(const T& value);
    bool remove(const T& value);
    bool contains(const T& value) const;
    T* find(const T& value);
    const T* find(const T& value) const;
    
    QList<T> inorderTraversal() const;
    QList<T> search(const QString& query) const;
    
    void clear();
    bool isEmpty() const;
    size_t size() const;
    
private:
    size_t sizeHelper(Node* node) const;
};

// Template implementation must be in header file
template<typename T>
BST<T>::BST() : root(nullptr) {
}

template<typename T>
void BST<T>::insert(const T& value) {
    insertHelper(root, value);
}

template<typename T>
void BST<T>::insertHelper(std::unique_ptr<Node>& node, const T& value) {
    if (!node) {
        node = std::make_unique<Node>(value);
        return;
    }
    
    if (value < node->data) {
        insertHelper(node->left, value);
    } else if (value > node->data) {
        insertHelper(node->right, value);
    }
    // If equal, don't insert (no duplicates)
}

template<typename T>
bool BST<T>::remove(const T& value) {
    return removeHelper(root, value);
}

template<typename T>
bool BST<T>::removeHelper(std::unique_ptr<Node>& node, const T& value) {
    if (!node) {
        return false;
    }
    
    if (value < node->data) {
        return removeHelper(node->left, value);
    } else if (value > node->data) {
        return removeHelper(node->right, value);
    } else {
        // Found the node to remove
        if (!node->left) {
            node = std::move(node->right);
        } else if (!node->right) {
            node = std::move(node->left);
        } else {
            // Node has two children - find inorder successor
            Node* successor = node->right.get();
            while (successor->left) {
                successor = successor->left.get();
            }
            node->data = successor->data;
            removeHelper(node->right, successor->data);
        }
        return true;
    }
}

template<typename T>
bool BST<T>::contains(const T& value) const {
    return findHelper(root.get(), value) != nullptr;
}

template<typename T>
T* BST<T>::find(const T& value) {
    Node* node = findHelper(root.get(), value);
    return node ? &(node->data) : nullptr;
}

template<typename T>
const T* BST<T>::find(const T& value) const {
    Node* node = findHelper(root.get(), value);
    return node ? &(node->data) : nullptr;
}

template<typename T>
typename BST<T>::Node* BST<T>::findHelper(Node* node, const T& value) const {
    if (!node) {
        return nullptr;
    }
    
    if (value == node->data) {
        return node;
    } else if (value < node->data) {
        return findHelper(node->left.get(), value);
    } else {
        return findHelper(node->right.get(), value);
    }
}

template<typename T>
QList<T> BST<T>::inorderTraversal() const {
    QList<T> result;
    inorderHelper(root.get(), result);
    return result;
}

template<typename T>
void BST<T>::inorderHelper(Node* node, QList<T>& result) const {
    if (node) {
        inorderHelper(node->left.get(), result);
        result.append(node->data);
        inorderHelper(node->right.get(), result);
    }
}

template<typename T>
QList<T> BST<T>::search(const QString& query) const {
    QList<T> results;
    QList<T> allItems = inorderTraversal();
    
    QString lowerQuery = query.toLower();
    for (const T& item : allItems) {
        if constexpr (std::is_same_v<T, Contact>) {
            if (item.getName().toLower().contains(lowerQuery) ||
                item.getPhone().contains(lowerQuery) ||
                item.getEmail().toLower().contains(lowerQuery)) {
                results.append(item);
            }
        }
    }
    
    return results;
}

template<typename T>
void BST<T>::clear() {
    clearHelper(root);
}

template<typename T>
void BST<T>::clearHelper(std::unique_ptr<Node>& node) {
    if (node) {
        clearHelper(node->left);
        clearHelper(node->right);
        node.reset();
    }
}

template<typename T>
bool BST<T>::isEmpty() const {
    return root == nullptr;
}

template<typename T>
size_t BST<T>::size() const {
    return sizeHelper(root.get());
}

template<typename T>
size_t BST<T>::sizeHelper(Node* node) const {
    if (!node) {
        return 0;
    }
    return 1 + sizeHelper(node->left.get()) + sizeHelper(node->right.get());
}

#endif // BST_H
