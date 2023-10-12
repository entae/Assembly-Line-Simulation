// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 11, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include <iostream>
#include <string>
#include "Cheese.h"

namespace sdds {

    //manages array of pointers but no the life of Cheese objects
    class CheeseParty {
        const Cheese** m_cheeses{nullptr};
        size_t m_numCheeses{0};

        void clear();
        void copyFrom(const CheeseParty& party);
        bool hasCheese(const Cheese& chez);
    public:
        CheeseParty()=default;
        virtual ~CheeseParty();
        //copy
        CheeseParty(const CheeseParty& party);
        CheeseParty operator=(const CheeseParty& party);
        //move
        CheeseParty(CheeseParty&& party);
        CheeseParty operator=(CheeseParty&& party);

        CheeseParty& addCheese(const Cheese& chez);
        CheeseParty& removeCheese();
    
        friend std::ostream& operator<<(std::ostream &os, const CheeseParty& party);
    };

}

#endif //!SDDS_CHEESEPARTY_H