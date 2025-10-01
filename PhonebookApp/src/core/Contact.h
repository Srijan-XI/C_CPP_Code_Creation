#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include <QDataStream>
#include <QMetaType>

class Contact {
public:
    Contact();
    Contact(const QString& name, const QString& phone, const QString& email = "");
    
    // Getters
    QString getName() const { return m_name; }
    QString getPhone() const { return m_phone; }
    QString getEmail() const { return m_email; }
    int getId() const { return m_id; }
    
    // Setters
    void setName(const QString& name) { m_name = name; }
    void setPhone(const QString& phone) { m_phone = phone; }
    void setEmail(const QString& email) { m_email = email; }
    void setId(int id) { m_id = id; }
    
    // Operators for BST comparison
    bool operator<(const Contact& other) const;
    bool operator>(const Contact& other) const;
    bool operator==(const Contact& other) const;
    
    // Serialization
    friend QDataStream& operator<<(QDataStream& stream, const Contact& contact);
    friend QDataStream& operator>>(QDataStream& stream, Contact& contact);
    
    // Validation
    bool isValid() const;
    
private:
    int m_id;
    QString m_name;
    QString m_phone;
    QString m_email;
    
    static int s_nextId;
};

Q_DECLARE_METATYPE(Contact)

#endif // CONTACT_H
