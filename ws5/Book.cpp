// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 23, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Book.h"
#include <iomanip>

namespace sdds {

    Book::Book(const std::string &strBook) {
        size_t pos1 = strBook.find(',');
        size_t pos2 = strBook.find(',', pos1 + 1);
        size_t pos3 = strBook.find(',', pos2 + 1);
        size_t pos4 = strBook.find(',', pos3 + 1);
        size_t pos5 = strBook.find(',', pos4 + 1);

        // Extract and set the member variables with trimmed spaces
        m_author = trimSpaces(strBook.substr(0, pos1));
        m_title = trimSpaces(strBook.substr(pos1 + 2, pos2 - pos1 - 2));
        m_country = trimSpaces(strBook.substr(pos2 + 2, pos3 - pos2 - 2));
        m_price = std::stod(strBook.substr(pos3 + 2, pos4 - pos3 - 2));
        m_year = std::stoi(strBook.substr(pos4 + 2, pos5 - pos4 - 2));

        // The description is everything after the last ','
        m_desc = trimSpaces(strBook.substr(pos5 + 1));
    }

    std::string Book::trimSpaces(const std::string &str) const {
        size_t start = str.find_first_not_of(' ');
        if (start == std::string::npos) {
            return "";
        }
        size_t end = str.find_last_not_of(' ');
        return str.substr(start, end - start + 1);
    }

    
    //queries
    const std::string& Book::title() const { return m_title; }
    const std::string& Book::country() const { return m_country; }
    const size_t& Book::year() const { return m_year; }
    double& Book::price() { return m_price; }

    bool Book::isEmpty() const {
        return m_title.empty();
    }

    void Book::display(std::ostream &os)const {
         //os << ' ';
         os.width(20); 
         os << std::right << m_author << " | ";
         os.width(22);
         os << std::right << m_title << " | ";
         os.width(5);
         os << m_country << " | ";
         os.width(4);
         os << m_year << " | ";
         os.precision(2);
         os.width(6);
         os << std::fixed << m_price << " | "
         << m_desc << std::endl;
    }

    std::ostream &operator<<(std::ostream &os, const Book &book) {
        book.display(os);
        return os;
    }

}