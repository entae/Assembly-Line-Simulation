// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 11, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "CheeseParty.h"

namespace sdds {

    void CheeseParty::clear() {
        delete[] m_cheeses;
        m_cheeses = nullptr;
        m_numCheeses = 0;
    }

    void CheeseParty::copyFrom(const CheeseParty& party) {
        m_cheeses = new const Cheese*[party.m_numCheeses];
        for (size_t i = 0; i < party.m_numCheeses; ++i) {
            m_cheeses[i] = party.m_cheeses[i];
        }
        m_numCheeses = party.m_numCheeses;
    }

    bool CheeseParty::hasCheese(const Cheese& chez) {
        bool has = false;
        for (size_t i = 0; i < m_numCheeses; ++i) {
            if (m_cheeses[i] == &chez) {
                has = true;
            }
        }
        return has;
    }

    CheeseParty::~CheeseParty() {
        clear();
    }

    CheeseParty::CheeseParty(const CheeseParty& party) :
        m_cheeses(nullptr), m_numCheeses(0) {
        copyFrom(party);
    }

    CheeseParty CheeseParty::operator=(const CheeseParty& party) {
        if (this != &party) {
            clear();
            copyFrom(party);
        }
        return *this;
    }

    CheeseParty::CheeseParty(CheeseParty&& party):
        m_cheeses(party.m_cheeses), m_numCheeses(party.m_numCheeses) {
            party.m_cheeses = nullptr;
            party.m_numCheeses = 0;
    }

    CheeseParty CheeseParty::operator=(CheeseParty&& party) {
        if (this != &party) {

            clear();

            m_numCheeses = std::move(party.m_numCheeses);
            m_cheeses = std::move(party.m_cheeses);

            party.m_numCheeses = 0;
            party.m_cheeses = nullptr;
        }
        return *this;
    }

    CheeseParty &CheeseParty::addCheese(const Cheese &chez) {
        if (!hasCheese(chez)) {
            const Cheese** temp = new const Cheese*[m_numCheeses+1];
            for (size_t i = 0; i < m_numCheeses; ++i) {
                temp[i] = m_cheeses[i];
            }
            temp[m_numCheeses] = &chez;
            delete[] m_cheeses;
            m_cheeses = temp;
            m_numCheeses++;
        }
        return *this;
    }

    CheeseParty &CheeseParty::removeCheese() {
        for (size_t i = 0; i < m_numCheeses; ++i) {
            if (m_cheeses[i] && m_cheeses[i]->getWeight() == 0) {
                m_cheeses[i] = nullptr;
            }
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream &os, const CheeseParty& party) {
        os << "--------------------------" << std::endl;
        os << "Cheese Party" << std::endl;
        os << "--------------------------" << std::endl;
        if (party.m_numCheeses == 0) {
            os << "This party is just getting started!" << std::endl;
        } else {
            for (size_t i = 0; i < party.m_numCheeses; ++i) {
                if (party.m_cheeses[i]) {
                    os << *(party.m_cheeses[i]);
                }
            }
        }
        os << "--------------------------" << std::endl;
        return os;
    }

}