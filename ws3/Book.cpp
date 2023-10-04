// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 1, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <iomanip>
#include "Book.h"

namespace sdds {
    Book::Book() {};
    Book::Book(const std::string& title, unsigned numChapters, unsigned numPages) {};

    Book::operator bool()const {
        return m_title.empty() || m_numChapters == 0 || m_numPages == 0;
    }

    std::ostream& Book::print(std::ostream &os)const {
        if (!this) {
            os << std::right;
            os.width(56);
            os << m_title << ',' << m_numChapters 
            << ',' << m_numPages << " | (";

            double avgPagesPerChapter = static_cast<double>(m_numPages) / m_numChapters;
            os.width(15);
            os << std::left << std::fixed << std::setprecision(6) << avgPagesPerChapter << ")    "; 
        } else {
            os << "| Invalid book data";
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Book &other) {
        return other.print(os);
    }
    

}