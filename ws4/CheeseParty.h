// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 1, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include <iostream>
#include <string>
#include "Cheese.h"

namespace sdds {

    //manages array of pointers but no the life of Cheese objects
    class CheeseParty {
        const Cheese** m_cheeses{};
        size_t m_numCheeses{};

        bool hasCheese(const Cheese* chez)const;
        void clear();
    public:
        CheeseParty()=default;
        CheeseParty& addCheese(const Cheese& chez);
        CheeseParty& removeCheese();
    
        std::ostream& display(std::ostream &os)const;
    };
    auto operator<<(std::ostream &os, CheeseParty& party) ->std::ostream&;
}

#endif //!SDDS_CHEESEPARTY_H