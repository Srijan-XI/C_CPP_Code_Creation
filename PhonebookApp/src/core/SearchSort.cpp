#include "SearchSort.h"
#include <algorithm>

QList<Contact> SearchSort::searchByName(const QList<Contact>& contacts, const QString& name) {
    QString lowerName = name.toLower();
    return linearSearch<Contact>(contacts, [&lowerName](const Contact& contact) {
        return contact.getName().toLower().contains(lowerName);
    });
}

QList<Contact> SearchSort::searchByPhone(const QList<Contact>& contacts, const QString& phone) {
    return linearSearch<Contact>(contacts, [&phone](const Contact& contact) {
        return contact.getPhone().contains(phone);
    });
}

QList<Contact> SearchSort::searchByEmail(const QList<Contact>& contacts, const QString& email) {
    QString lowerEmail = email.toLower();
    return linearSearch<Contact>(contacts, [&lowerEmail](const Contact& contact) {
        return contact.getEmail().toLower().contains(lowerEmail);
    });
}

QList<Contact> SearchSort::fuzzySearch(const QList<Contact>& contacts, const QString& query) {
    QList<Contact> results;
    QString lowerQuery = query.toLower();
    
    // Define fuzzy match threshold (maximum edit distance)
    const int maxDistance = 2;
    
    for (const Contact& contact : contacts) {
        bool isMatch = false;
        
        // Check exact substring match first (faster)
        if (contact.getName().toLower().contains(lowerQuery) ||
            contact.getPhone().contains(query) ||
            contact.getEmail().toLower().contains(lowerQuery)) {
            isMatch = true;
        } else {
            // Check fuzzy match for name
            QStringList nameWords = contact.getName().toLower().split(' ', Qt::SkipEmptyParts);
            for (const QString& word : nameWords) {
                if (levenshteinDistance(word, lowerQuery) <= maxDistance) {
                    isMatch = true;
                    break;
                }
            }
        }
        
        if (isMatch) {
            results.append(contact);
        }
    }
    
    return results;
}

void SearchSort::sortByName(QList<Contact>& contacts) {
    std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return a.getName().toLower() < b.getName().toLower();
    });
}

void SearchSort::sortByPhone(QList<Contact>& contacts) {
    std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return a.getPhone() < b.getPhone();
    });
}

void SearchSort::sortByEmail(QList<Contact>& contacts) {
    std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return a.getEmail().toLower() < b.getEmail().toLower();
    });
}

int SearchSort::levenshteinDistance(const QString& s1, const QString& s2) {
    const int len1 = s1.length();
    const int len2 = s2.length();
    
    if (len1 == 0) return len2;
    if (len2 == 0) return len1;
    
    QVector<QVector<int>> matrix(len1 + 1, QVector<int>(len2 + 1));
    
    // Initialize first row and column
    for (int i = 0; i <= len1; ++i) {
        matrix[i][0] = i;
    }
    for (int j = 0; j <= len2; ++j) {
        matrix[0][j] = j;
    }
    
    // Fill the matrix
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            int cost = (s1[i-1] == s2[j-1]) ? 0 : 1;
            
            matrix[i][j] = std::min({
                matrix[i-1][j] + 1,    // deletion
                matrix[i][j-1] + 1,    // insertion
                matrix[i-1][j-1] + cost // substitution
            });
        }
    }
    
    return matrix[len1][len2];
}
