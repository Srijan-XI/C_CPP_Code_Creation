#ifndef SEARCHSORT_H
#define SEARCHSORT_H

#include <QList>
#include <QString>
#include <functional>
#include "Contact.h"

class SearchSort {
public:
    // Search algorithms
    template<typename T>
    static QList<T> linearSearch(const QList<T>& data, const std::function<bool(const T&)>& predicate);
    
    template<typename T>
    static int binarySearch(const QList<T>& sortedData, const T& target, const std::function<bool(const T&, const T&)>& comparator);
    
    // Sorting algorithms
    template<typename T>
    static void quickSort(QList<T>& data, const std::function<bool(const T&, const T&)>& comparator);
    
    template<typename T>
    static void mergeSort(QList<T>& data, const std::function<bool(const T&, const T&)>& comparator);
    
    // Contact-specific search methods
    static QList<Contact> searchByName(const QList<Contact>& contacts, const QString& name);
    static QList<Contact> searchByPhone(const QList<Contact>& contacts, const QString& phone);
    static QList<Contact> searchByEmail(const QList<Contact>& contacts, const QString& email);
    static QList<Contact> fuzzySearch(const QList<Contact>& contacts, const QString& query);
    
    // Contact-specific sorting methods
    static void sortByName(QList<Contact>& contacts);
    static void sortByPhone(QList<Contact>& contacts);
    static void sortByEmail(QList<Contact>& contacts);
    
private:
    template<typename T>
    static void quickSortHelper(QList<T>& data, int low, int high, const std::function<bool(const T&, const T&)>& comparator);
    
    template<typename T>
    static int partition(QList<T>& data, int low, int high, const std::function<bool(const T&, const T&)>& comparator);
    
    template<typename T>
    static void mergeSortHelper(QList<T>& data, int left, int right, const std::function<bool(const T&, const T&)>& comparator);
    
    template<typename T>
    static void merge(QList<T>& data, int left, int mid, int right, const std::function<bool(const T&, const T&)>& comparator);
    
    static int levenshteinDistance(const QString& s1, const QString& s2);
};

// Template implementations
template<typename T>
QList<T> SearchSort::linearSearch(const QList<T>& data, const std::function<bool(const T&)>& predicate) {
    QList<T> results;
    for (const T& item : data) {
        if (predicate(item)) {
            results.append(item);
        }
    }
    return results;
}

template<typename T>
int SearchSort::binarySearch(const QList<T>& sortedData, const T& target, const std::function<bool(const T&, const T&)>& comparator) {
    int left = 0;
    int right = sortedData.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (sortedData[mid] == target) {
            return mid;
        } else if (comparator(sortedData[mid], target)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Not found
}

template<typename T>
void SearchSort::quickSort(QList<T>& data, const std::function<bool(const T&, const T&)>& comparator) {
    if (data.size() <= 1) {
        return;
    }
    quickSortHelper(data, 0, data.size() - 1, comparator);
}

template<typename T>
void SearchSort::quickSortHelper(QList<T>& data, int low, int high, const std::function<bool(const T&, const T&)>& comparator) {
    if (low < high) {
        int pi = partition(data, low, high, comparator);
        quickSortHelper(data, low, pi - 1, comparator);
        quickSortHelper(data, pi + 1, high, comparator);
    }
}

template<typename T>
int SearchSort::partition(QList<T>& data, int low, int high, const std::function<bool(const T&, const T&)>& comparator) {
    T pivot = data[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (comparator(data[j], pivot)) {
            i++;
            data.swapItemsAt(i, j);
        }
    }
    
    data.swapItemsAt(i + 1, high);
    return i + 1;
}

template<typename T>
void SearchSort::mergeSort(QList<T>& data, const std::function<bool(const T&, const T&)>& comparator) {
    if (data.size() <= 1) {
        return;
    }
    mergeSortHelper(data, 0, data.size() - 1, comparator);
}

template<typename T>
void SearchSort::mergeSortHelper(QList<T>& data, int left, int right, const std::function<bool(const T&, const T&)>& comparator) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(data, left, mid, comparator);
        mergeSortHelper(data, mid + 1, right, comparator);
        merge(data, left, mid, right, comparator);
    }
}

template<typename T>
void SearchSort::merge(QList<T>& data, int left, int mid, int right, const std::function<bool(const T&, const T&)>& comparator) {
    QList<T> leftArray, rightArray;
    
    for (int i = left; i <= mid; i++) {
        leftArray.append(data[i]);
    }
    for (int i = mid + 1; i <= right; i++) {
        rightArray.append(data[i]);
    }
    
    int i = 0, j = 0, k = left;
    
    while (i < leftArray.size() && j < rightArray.size()) {
        if (comparator(leftArray[i], rightArray[j])) {
            data[k] = leftArray[i];
            i++;
        } else {
            data[k] = rightArray[j];
            j++;
        }
        k++;
    }
    
    while (i < leftArray.size()) {
        data[k] = leftArray[i];
        i++;
        k++;
    }
    
    while (j < rightArray.size()) {
        data[k] = rightArray[j];
        j++;
        k++;
    }
}

#endif // SEARCHSORT_H
