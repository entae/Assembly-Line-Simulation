// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 1, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <iostream>
#include <string>
#include "Cheese.h"

namespace sdds {

    //this class is responsible for managing both the array and the Cheese objects
    class CheeseShop {
       std::string m_shopName;
       const Cheese** m_cheeses;
       size_t m_numCheeses;
    public:
        CheeseShop(const std::string& name = "No Name");

        //copy constructor;
        CheeseShop(const CheeseShop& chez);
        //assignment op
        CheeseShop& operator=(const CheeseShop& chez);
        //destructor
        virtual ~CheeseShop();
        //movers
        CheeseShop(CheeseShop&& chez);
        CheeseShop& operator=(CheeseShop&& chez);

        //clears DMA
        void clear();
        CheeseShop& addCheese(const Cheese& chez);
        
        //getters
        // auto getShopName()const ->std::string;
        // auto getCheeseArr()const ->const Cheese**;
        // auto getNumCheeses()const ->size_t;

        std::ostream& display(std::ostream& os)const;
    };
    // Helper
    auto operator<<(std::ostream& os, CheeseShop& shop)-> std::ostream&; 

}

#endif //!SDDS_CHEESESHOP_H