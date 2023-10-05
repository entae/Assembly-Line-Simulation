// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 1, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>
#include "Book.h"

namespace sdds {

// T = type of element of managed array, called m_items
// unsigned C = unsigned int value; capacity of collection
// no conditions needed
template <typename T, unsigned C>

class Collection {
    static T m_smallestItem;
    static T m_largestItem;

    T m_items[C];
    size_t m_size{};

// Protected:
//      can be accessed by derived classes/child classes 
protected:
    void setSmallestItem(const T& newSmallest) {
        if (newSmallest < m_smallestItem) {
            m_smallestItem = newSmallest;
        }
    };
    void setLargestItem(const T& newLargest) {
        if (newLargest > m_largestItem) {
            m_largestItem = newLargest;
        }
    }

    T& operator[](size_t index) {
        if (index < m_size) {
            return m_items[index];
        }
        throw std::out_of_range("Index out of range");
    }

    void incrSize() {
        if (m_size < C) {
            m_size++;
        }
    }

public:
    Collection() = default;
    ~Collection() = default;

    static T getSmallestItem() {
        return m_smallestItem;
    }

    static T getLargestItem() {
        return m_largestItem;
    }

    unsigned size()const {
        return m_size;
    }

    unsigned capacity()const {
        return C;
    }

    operator bool()const {
        return m_size;
    }

    bool operator+=(const T& item) {
        bool added = false;
        if (m_size < C) {
            setSmallestItem(item);
            setLargestItem(item);
            m_items[m_size++] = item;
            added = true;
        }
        return added;
    }

    std::ostream& print(std::ostream& os)const {
        os << '[';
        for (size_t i = 0; i < m_size - 1; i++) {
            os << std::setprecision(1) << m_items[i] << ',';
        }
        return os << m_items[m_size - 1 ] << ']' << std::endl;
    }
};

//initializing static members outside class
template <typename T, unsigned C> // Initialize to 9999
T Collection<T, C>::m_smallestItem = T(9999);

template <typename T, unsigned C> // Initialize to -9999
T Collection<T, C>::m_largestItem = T(-9999);

//specialized definition for T=Book and C=10
template<>
Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);
template<>
Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);
//specialized definition for T=Book and C=72
template<>
Book Collection<Book, 72>::m_smallestItem("", 1, 10000);
template<>
Book Collection<Book, 72>::m_largestItem("", 10000, 1);

template<>
std::ostream& Collection<Book, 10>::print(std::ostream& os)const {
    if (*this) {
        os << '|' << std::string(76, '-') << '|' << std::endl;
        for (size_t i = 0; i < m_size; i++) {
            os << "| ";
            m_items[i].print(os) << '|' << std::endl;
        }
        os << '|' << std::string(76, '-') << '|' << std::endl;
    }
    return os;
}

template<>
std::ostream& Collection<Book, 72>::print(std::ostream& os)const {
    if (*this) {
        os << '|' << std::string(76, '-') << '|' << std::endl;
        for (size_t i = 0; i < m_size; i++) {
            os << "| ";
            m_items[i].print(os) << '|' << std::endl;
        }
        os << '|' << std::string(76, '-') << '|' << std::endl;
    }
    return os;
}

}

#endif // !SDDS_COLLECTION_H