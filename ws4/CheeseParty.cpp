// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 1, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "CheeseParty.h"

namespace sdds {

    bool CheeseParty::hasCheese(const Cheese *chez) const {
        bool exists = false;
        for (size_t i = 0; i < m_numCheeses; i++) {
            if (m_cheeses[i] == chez) {
                exists = true;
            }
        }
        return exists;
    }

    void CheeseParty::clear() {
        for (size_t i = 0; i < m_numCheeses; i++) {
            delete m_cheeses[i];
        }
        delete[] m_cheeses;
        m_cheeses = nullptr;
        m_numCheeses = 0;
    }

    CheeseParty::~CheeseParty() {
        clear();
    }

    CheeseParty::CheeseParty(const CheeseParty& party) {
        m_numCheeses = party.m_numCheeses;
        m_cheeses = nullptr;
        if (party.m_numCheeses > 0) {
            m_cheeses = new const Cheese*[party.m_numCheeses];
            for (size_t i = 0; i < party.m_numCheeses; i++) {
                m_cheeses[i] = new Cheese(*(party.m_cheeses[i]));        
            }
        }
    }

    CheeseParty CheeseParty::operator=(const CheeseParty& party) {
        if (this != &party) {
            clear();
            m_numCheeses = party.m_numCheeses;

            if (m_numCheeses > 0) {
                m_cheeses = new const Cheese*[m_numCheeses];

                for (size_t i = 0; i < m_numCheeses; i++) {
                    m_cheeses[i] = new Cheese(*(party.m_cheeses[i]));
                }
            }
        }
        return *this;
    }

    CheeseParty::CheeseParty(CheeseParty&& party) {
        clear();
        m_numCheeses = std::move(party.m_numCheeses);
        m_cheeses = std::move(party.m_cheeses);

        party.m_numCheeses = 0;
        party.m_cheeses = nullptr;
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
        if (!hasCheese(&chez)) {
            const Cheese** temp = new const Cheese*[m_numCheeses+1];
            for (size_t i = 0; i < m_numCheeses; i++) {
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
        
        size_t removed = 0;
        const Cheese** temp = new const Cheese*[m_numCheeses];

        for (size_t i = 0; i < m_numCheeses; i++) {
            if (m_cheeses[i] && m_cheeses[i]->getWeight() != 0.0) {
                temp[i - removed] = m_cheeses[i];
            } else {
                removed++;
            }
        }

        if (removed > 0) {
            const Cheese** newCheeses = new const Cheese*[m_numCheeses - removed];
            for (size_t i = 0; i < m_numCheeses - removed; i++) {
                newCheeses[i] = temp[i];
            }
            delete[] m_cheeses;
            m_cheeses = newCheeses;
            m_numCheeses -= removed;
        }

        delete[] temp;
        return *this;
    }

    std::ostream& CheeseParty::display(std::ostream& os)const {
        os << "--------------------------" << std::endl;
        os << "Cheese Party" << std::endl;
        os << "--------------------------" << std::endl;
        if (m_numCheeses == 0) {
            os << "This party is just getting started!" << std::endl;
        } else {
            for (size_t i = 0; i < m_numCheeses; i++) {
                if (m_cheeses[i]) {
                    os << *(m_cheeses[i]);
                }
            }
        }
        os << "--------------------------" << std::endl;
        return os;
    }

    auto operator<<(std::ostream& os, CheeseParty& party) ->std::ostream& {
        return party.display(os);
    }
}