// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 23, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "SpellChecker.h"

#include <iostream>
#include <fstream>
#include <iomanip>

namespace sdds {

    SpellChecker::SpellChecker(const char* filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::invalid_argument("Bad file name!");
        } else {
            for (size_t i = 0; i < MAX_WORDS; i++) {
                file >> m_bad[i];
                file >> m_good[i];
            }
        }
        file.close();
    }

    void SpellChecker::operator()(std::string& text) {
        for (size_t i = 0; i < MAX_WORDS; i++) {
            size_t pos = text.find(m_bad[i]);
            while (pos != std::string::npos) {
                text.replace(pos, m_bad[i].length(), m_good[i]);
                m_replaced[i]++;
                pos = text.find(m_bad[i], pos + m_good[i].length());
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out)const {
        std::cout << "Spellchecker Statistics" << std::endl;
        for (size_t i = 0; i < MAX_WORDS; i++) {
            out << std::setw(15) << std::right << m_bad[i] << ": " << m_replaced[i] << " replacements" << std::endl;
        }
    }

}
