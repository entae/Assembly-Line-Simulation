// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 11, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <iostream>
#include <string>
#include "Cheese.h"

namespace sdds {

    //this class is responsible for managing both the array and the Cheese objects
    class CheeseShop : public Cheese {
       std::string m_shopName {"No Name"};
       const Cheese** m_cheeses {};
       size_t m_numCheeses {};

       void clear();
       void copyFrom(const CheeseShop& other);
    public:
        CheeseShop(const std::string& name = "No Name");
        
        //destructor
        virtual ~CheeseShop();

        //copy constructor;
        CheeseShop(const CheeseShop& chez);
        //assignment op
        CheeseShop& operator=(const CheeseShop& chez);
        
        //movers
        CheeseShop(CheeseShop&& chez);
        CheeseShop& operator=(CheeseShop&& chez);

        CheeseShop& addCheese(const Cheese& chez);

        friend std::ostream& operator<<(std::ostream& os, const CheeseShop& shop);
    };

}

#endif //!SDDS_CHEESESHOP_H