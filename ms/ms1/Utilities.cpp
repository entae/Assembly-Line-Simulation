// Name:                In Tae Chung
// Seneca Student ID:   128 958 220
// Seneca email:        itchung@myseneca.ca
// Date of completion:  Nov. 19, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

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
        std::string token;

        size_t delimiterPos = str.find(m_delimiter, next_pos);

        if (delimiterPos != std::string::npos) {
            token = str.substr(next_pos, delimiterPos - next_pos);
            token = trim(token);  // Trim the token first
            next_pos = delimiterPos + 1;
            more = true;

            // Update field width if needed
            if (token.length() > m_widthField) {
                m_widthField = token.length();
            }
        } else {
            if (next_pos < str.length()) {
                token = str.substr(next_pos, str.length() - next_pos);
                token = trim(token);  // Trim the token first
                next_pos = str.length();  // Ensure next_pos is set to the end of the string
                more = false;
            } else {
                // No more tokens, throw an exception for an empty token
                more = false;
                throw std::string("ERROR: No token.");
            }
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