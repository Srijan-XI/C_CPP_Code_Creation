#include "Contact.h"
#include <QRegularExpression>

int Contact::s_nextId = 1;

Contact::Contact() : m_id(s_nextId++), m_name(""), m_phone(""), m_email("") {
}

Contact::Contact(const QString& name, const QString& phone, const QString& email)
    : m_id(s_nextId++), m_name(name.trimmed()), m_phone(phone.trimmed()), m_email(email.trimmed()) {
}

bool Contact::operator<(const Contact& other) const {
    return m_name.toLower() < other.m_name.toLower();
}

bool Contact::operator>(const Contact& other) const {
    return m_name.toLower() > other.m_name.toLower();
}

bool Contact::operator==(const Contact& other) const {
    return m_name.toLower() == other.m_name.toLower() && m_phone == other.m_phone;
}

QDataStream& operator<<(QDataStream& stream, const Contact& contact) {
    stream << contact.m_id << contact.m_name << contact.m_phone << contact.m_email;
    return stream;
}

QDataStream& operator>>(QDataStream& stream, Contact& contact) {
    stream >> contact.m_id >> contact.m_name >> contact.m_phone >> contact.m_email;
    if (contact.m_id >= Contact::s_nextId) {
        Contact::s_nextId = contact.m_id + 1;
    }
    return stream;
}

bool Contact::isValid() const {
    if (m_name.isEmpty() || m_phone.isEmpty()) {
        return false;
    }
    
    // Basic phone number validation (digits, spaces, hyphens, parentheses, plus sign)
    QRegularExpression phoneRegex("^[\\d\\s\\-\\(\\)\\+]+$");
    if (!phoneRegex.match(m_phone).hasMatch()) {
        return false;
    }
    
    // Basic email validation if provided
    if (!m_email.isEmpty()) {
        QRegularExpression emailRegex("^[\\w\\._%+-]+@[\\w\\.-]+\\.[A-Za-z]{2,}$");
        if (!emailRegex.match(m_email).hasMatch()) {
            return false;
        }
    }
    
    return true;
}
