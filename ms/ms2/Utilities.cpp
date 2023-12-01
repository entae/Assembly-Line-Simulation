// Name:                In Tae Chung
// Seneca Student ID:   128 958 220
// Seneca email:        itchung@myseneca.ca
// Date of completion:  Nov. 19, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Utilities.h"

namespace sdds {
    // initialize delim as whitespace
    char Utilities::m_delimiter = ' ';

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }
    size_t Utilities::getFieldWidth()const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        size_t pos = str.find(m_delimiter, next_pos);

        if (pos == next_pos) {
            more = false;
            throw "Error Occurred";
        }

        std::string token = (pos != std::string::npos) ? str.substr(next_pos, pos - next_pos) : str.substr(next_pos);
        more = (pos != std::string::npos);

        if (!token.empty()) {
            token = trim(token);
            next_pos = pos + 1;

            if (token.length() >= m_widthField) {
                setFieldWidth(token.length());
            }

        } else {
            more = false;
        }

        return token;
    }

    // Trim whitespace from the beginning and end of a string
    std::string Utilities::trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r\f\v");
        size_t last = str.find_last_not_of(" \t\n\r\f\v");

        if (first == std::string::npos || last == std::string::npos) {
            // The string is empty or contains only whitespace
            return "";
        }

        return str.substr(first, last - first + 1);
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }

}