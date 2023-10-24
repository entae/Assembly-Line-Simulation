// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 11, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Book.h"
#include <iomanip>

namespace sdds {

    Book::Book(const std::string &strBook) {
        // Find the positions of '|' characters
        size_t pos1 = strBook.find(',');
        size_t pos2 = strBook.find(',', pos1 + 1);
        size_t pos3 = strBook.find(',', pos2 + 1);
        size_t pos4 = strBook.find(',', pos3 + 1);

        // Extract and set the member variables
        m_author = strBook.substr(0, pos1);
        m_title = strBook.substr(pos1 + 2, pos2 - pos1 - 2);
        m_country = strBook.substr(pos2 + 2, pos3 - pos2 - 2);
        m_year = std::stoi(strBook.substr(pos3 + 2, pos4 - pos3 - 2));
        m_price = std::stod(strBook.substr(pos4 + 2));

        // The description is everything after the last '|'
        m_desc = strBook.substr(pos4 + 2);
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
         os.width(20); 
         os << std::left << m_author << " | ";
         os.width(22);
         os << m_title << " | ";
         os.width(5);
         os << m_country << " | ";
         os.width(4);
         os << m_year << " | ";
         os.precision(2);
         os.width(6);
         os << m_price << " | "
         << m_desc << std::endl;
    }

    std::ostream &operator<<(std::ostream &os, const Book &book) {
        book.display(os);
        return os;
    }

}