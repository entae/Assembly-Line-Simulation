// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 1, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "CheeseShop.h"

namespace sdds {
    
    CheeseShop::CheeseShop(const std::string& name) :
        m_shopName(name), m_cheeses(nullptr), m_numCheeses(0) {}

    CheeseShop::CheeseShop(const CheeseShop& chez) {
        *this = chez;

        // m_shopName = "";
        // m_shopName = chez.m_shopName;
        // m_numCheeses = chez.m_numCheeses;
        // m_cheeses = new const Cheese*[m_numCheeses];
        // for (size_t i = 0; i < m_numCheeses; i++) {
        //     m_cheeses[i] = new Cheese(*(chez.m_cheeses[i]));
    }

    CheeseShop& CheeseShop::operator=(const CheeseShop& chez) {
        //std::cout << "COPYING!" << std::endl;
        if (this != &chez) {
            clear();
            // m_shopName = "";
            m_shopName = chez.m_shopName;
            m_numCheeses = chez.m_numCheeses;
            
            if (chez.m_numCheeses > 0) {
                //new memory allocations
                m_cheeses = new const Cheese*[m_numCheeses];

                for (size_t i = 0; i < m_numCheeses; i++) {
                    m_cheeses[i] = new Cheese(*(chez.m_cheeses[i]));
                }
            }
            // const Cheese** temp = new const Cheese* [chez.m_numCheeses];

            // for (size_t i = 0; i < chez.m_numCheeses; i++) {
            //     temp[i] = chez.m_cheeses[i];
            // }
            // delete[] m_cheeses;
            // temp = m_cheeses;
            // m_shopName = chez.m_shopName;
            // m_numCheeses = chez.m_numCheeses;
        }
        return *this;
    }

    CheeseShop::~CheeseShop() {
        clear();
    }

    CheeseShop::CheeseShop(CheeseShop&& chez)noexcept {
        *this = std::move(chez);

        // m_shopName = std::move(chez.m_shopName);
        // m_numCheeses = std::move(chez.m_numCheeses);
        // m_cheeses = std::move(chez.m_cheeses);

        // chez.m_cheeses = nullptr;
        // chez.m_numCheeses = 0;
    }

    CheeseShop& CheeseShop::operator=(CheeseShop&& chez)noexcept {
        //std::cout << "MOVING!!" << std::endl;
        if (this != &chez) {

            clear();
            m_shopName = std::move(chez.m_shopName);
            m_cheeses = std::move(chez.m_cheeses);
            chez.m_cheeses = nullptr;
            m_numCheeses = std::move(chez.m_numCheeses);
            chez.m_numCheeses = 0;

            // for (size_t i = 0; i < m_numCheeses; i++) {
            //     delete m_cheeses[i];
            // }
            // delete[] m_cheeses;

            // m_shopName = std::move(chez.m_shopName);
            // m_numCheeses = std::move(chez.m_numCheeses);
            // m_cheeses = std::move(chez.m_cheeses);

            // chez.m_cheeses = nullptr;
            // chez.m_numCheeses = 0;

            // delete[] m_cheeses;
            // m_cheeses = nullptr;

            // m_cheeses = chez.m_cheeses;
            // m_numCheeses = chez.m_numCheeses;
            // m_shopName = std::move(chez.m_shopName);
            // chez.clear();
        }
        return *this;
    }

    void CheeseShop::clear() {
        if (m_cheeses) {
            for (size_t i = 0; i < m_numCheeses; i++) {
                delete m_cheeses[i];
            }
            delete[] m_cheeses;
            m_cheeses = nullptr;
            m_numCheeses = 0;
            // m_shopName = "";
        }
    }

    CheeseShop &CheeseShop::addCheese(const Cheese& chez) {
        const Cheese** temp = new const Cheese*[m_numCheeses + 1];
        for (size_t i = 0; i < m_numCheeses; i++) {
            temp[i] = m_cheeses[i];
        }
        temp[m_numCheeses] = new const Cheese(chez);
        delete[] m_cheeses;
        m_cheeses = temp;
        m_numCheeses++;
        return *this;
    }

    std::ostream &CheeseShop::display(std::ostream &os)const {
        os << "--------------------------" << std::endl;
        os << m_shopName << std::endl;
        os << "--------------------------" << std::endl;
        if (m_numCheeses == 0) {
            os << "This shop is out of cheese!" << std::endl;
        } else {
            for (size_t i = 0; i < m_numCheeses; i++) {
                os << *(m_cheeses[i]);
            }
        }
        os << "--------------------------" << std::endl;
        return os;
    }

    auto operator<<(std::ostream& os, CheeseShop& shop) ->std::ostream& {
        return shop.display(os);
    }
}