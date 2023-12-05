// Name:                In Tae Chung
// Seneca Student ID:   128 958 220
// Seneca email:        itchung@myseneca.ca
// Date of completion:  Nov. 19, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

namespace sdds {

class Utilities {
    size_t m_widthField{1};
    static char m_delimiter;

public:
    // sets fieldWidth of current obj to value of 'newWidth'
    void setFieldWidth(size_t newWidth);
    // returns field width of current obj
    size_t getFieldWidth()const;

    // extracts token from string str referred to by first param
    std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

    std::string trim(const std::string& str);

    // class functions:
    // sets the delim for this class to the char received
    static void setDelimiter(char newDelimiter);
    // returns the delim for this class
    static char getDelimiter();
};

}

#endif // !SDDS_UTILITIES_H