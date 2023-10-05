// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 1, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <iomanip>
#include "Book.h"

namespace sdds {
    Book::Book() {};
    Book::Book(const std::string& title, unsigned numChapters, unsigned numPages) : m_title(title), m_numChapters(numChapters), m_numPages(numPages) {};

    Book::operator bool()const {
        return m_title[0] != '\0' && m_numChapters > 0 && m_numPages > 0;
    }

    bool Book::operator<(const Book& RO)const {
        return ((double)m_numPages/m_numChapters) < ((double)RO.m_numPages/RO.m_numChapters);
    }

    bool Book::operator>(const Book& RO)const {
        return ((double)m_numPages/m_numChapters) > ((double)RO.m_numPages/RO.m_numChapters);
    }

    std::ostream& Book::print(std::ostream &os)const {
        if (*this) {
            os << std::setw(m_numChapters > 9 ? 49 : 50) 
                << std::right << m_title << ',' 
                << m_numChapters << ',' 
                << m_numPages << " | (" 

                << std::fixed << std::setprecision(6) << (double)m_numPages/m_numChapters << ")    ";
        } else {
            os << "| Invalid book data";
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Book &other) {
        return other.print(os);
    }
    

}