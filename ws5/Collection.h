// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 23, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iomanip>

namespace sdds {

template <typename T>
class Collection {
    std::string m_name{};
    T* m_items{};
    size_t m_size{};
    void (*m_observer)(const Collection<T>&, const T&) = nullptr;
    Collection(T&) = delete;
    Collection& operator=(T&) = delete;

public:
    Collection(const std::string& name) : m_name(name) {}

    ~Collection() {
        delete[] m_items;
    }

    const std::string& name() const {
        return m_name;
    }

    size_t size() const {
        return m_size;
    }

    void setObserver(void (*observer)(const Collection<T>& collection, const T& object)) {
        m_observer = observer;
    }

    Collection<T>& operator+=(const T& item) {
        bool exists = false;
        for (size_t i = 0; i < m_size; i++) {
            if (item.title() == m_items[i].title()) {
                exists = true;
            }
        }
        if (!exists) {
            T* newItems = new T[m_size + 1];
            for (size_t i = 0; i < m_size; i++) {
                newItems[i] = m_items[i];
            }
            delete[] m_items;
            newItems[m_size] = item;
            m_items = newItems;
            m_size++;
            if (m_observer) {
                m_observer(*this, item);
            }
        }
        return *this;
    }

    T& operator[](size_t idx) const {
        if (idx >= m_size) {
            throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items.");
        }
        return m_items[idx];
    }

    T* operator[](const std::string& title) const {
        for (size_t i = 0; i < m_size; i++) {
            if (m_items[i].title() == title) {
                return &m_items[i];
            }
        }
        return nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, const Collection<T>& collection) {
        for (size_t i = 0; i < collection.size(); i++) {
            os << collection[i];
        }
        return os;
    }
};

}

#endif