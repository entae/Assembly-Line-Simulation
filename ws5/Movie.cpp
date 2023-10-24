// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 23, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Movie.h"

#include <iostream>
#include <iomanip>

namespace sdds {

    Movie::Movie(const std::string& strMovie) {
        size_t pos1 = strMovie.find(',');
        size_t pos2 = strMovie.find(',', pos1 + 1);
        // size_t pos3 = strMovie.find(',', pos2 + 1);

        m_title = trimSpaces(strMovie.substr(0, pos1));
        m_year = std::stoi(strMovie.substr(pos1 + 2, pos2 - pos1 - 2));
        m_desc = trimSpaces(strMovie.substr(pos2 + 1));
    }

    const std::string& Movie::title()const {
        return m_title;
    }

     std::string Movie::trimSpaces(const std::string &str) const {
        size_t start = str.find_first_not_of(' ');
        if (start == std::string::npos) {
            return "";
        }
        size_t end = str.find_last_not_of(' ');
        return str.substr(start, end - start + 1);
    }

    void Movie::display(std::ostream &os)const {
         //os << ' ';
         os.width(40); 
         os << std::right << m_title << " | ";
         os.width(4);
         os << std::right << m_year << " | ";
         os << m_desc << std::endl;
    }

    std::ostream &operator<<(std::ostream &os, const Movie& movie) {
        movie.display(os);
        return os;
    }
}