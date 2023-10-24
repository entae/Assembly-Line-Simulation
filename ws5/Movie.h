// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 23, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H

#include <iostream>

namespace sdds {

class Movie {
    std::string m_title{};
    size_t m_year{};
    std::string m_desc{};
public:

    template <typename T>
    void fixSpelling(T& spellChecker) {
        spellChecker(m_title);
        spellChecker(m_desc);
    }

    Movie()=default;
    Movie(const std::string& strMovie);
    const std::string& title()const;
    std::string trimSpaces(const std::string& str)const;
    void display(std::ostream& os)const;
};

std::ostream& operator<<(std::ostream& os, const Movie& movie);


}

#endif