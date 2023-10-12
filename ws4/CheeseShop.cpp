// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 11, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "CheeseShop.h"

namespace sdds {
    
    void CheeseShop::clear() {
        for (size_t i = 0; i < m_numCheeses; ++i) {
            delete m_cheeses[i];
        }
        delete[] m_cheeses;
        m_cheeses = nullptr;
        m_numCheeses = 0;
    }
    
    void CheeseShop::copyFrom(const CheeseShop& chez) {
        m_cheeses = new const Cheese*[chez.m_numCheeses];
        for (size_t i = 0; i < chez.m_numCheeses; ++i) {
            m_cheeses[i] = new Cheese(*(chez.m_cheeses[i]));
        }
        m_numCheeses = chez.m_numCheeses;
    }

    CheeseShop::CheeseShop(const std::string& name) :
        m_shopName(name), m_cheeses(nullptr), m_numCheeses(0) {}

    CheeseShop::CheeseShop(const CheeseShop& chez) {
        copyFrom(chez);
    }

    CheeseShop& CheeseShop::operator=(const CheeseShop& chez) {
        //std::cout << "COPYING!" << std::endl;
        if (this != &chez) {
            clear();
            m_shopName = chez.m_shopName;
            copyFrom(chez);
        }
        return *this;
    }

    CheeseShop::~CheeseShop() {
        clear();
    }

    CheeseShop::CheeseShop(CheeseShop&& chez) :
        m_shopName(std::move(chez.m_shopName)),
        m_cheeses(chez.m_cheeses),
        m_numCheeses(chez.m_numCheeses) {
        
        chez.m_cheeses = nullptr;
        chez.m_numCheeses = 0;
    }

    CheeseShop& CheeseShop::operator=(CheeseShop&& chez) {
        //std::cout << "MOVING!!" << std::endl;
        if (this != &chez) {
            clear();
            m_shopName = std::move(chez.m_shopName);
            m_numCheeses = std::move(chez.m_numCheeses);
            m_cheeses = std::move(chez.m_cheeses);
            
            chez.m_shopName = "";
            chez.m_numCheeses = 0;
            chez.m_cheeses = nullptr;
        }
        return *this;
    }

    CheeseShop &CheeseShop::addCheese(const Cheese& chez) {
        const Cheese** temp = new const Cheese*[m_numCheeses + 1];
        for (size_t i = 0; i < m_numCheeses; ++i) {
            temp[i] = m_cheeses[i];
        }
        temp[m_numCheeses] = new Cheese(chez);
        delete[] m_cheeses;
        m_cheeses = temp;
        m_numCheeses++;
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const CheeseShop& shop) {
        os << "--------------------------" << std::endl;
        os << shop.m_shopName << std::endl;
        os << "--------------------------" << std::endl;
        if (shop.m_numCheeses == 0) {
            os << "This shop is out of cheese!" << std::endl;
        } else {
            for (size_t i = 0; i < shop.m_numCheeses; i++) {
                os << *(shop.m_cheeses[i]);
            }
        }
        os << "--------------------------" << std::endl;
        return os;
    }
}
