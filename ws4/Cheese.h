// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 1, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <iostream>

namespace sdds {

    //block of cheese that can be sliced into smaller cheeses
    class Cheese {
        std::string m_name{ "NaC" }; //defaults to NaC "Not a Cheese"
        size_t m_weight{};//in grams
        double m_price{}; //price per gram
        std::string m_desc{}; //features or description of cheese
    public:
        Cheese()=default;

        // decipher desc string and initialize as attributes
        // format: Name,Weight,Price,Feature1,Feature2,etc..
        // m_desc: "Hard Sharp Smooth Smelly"
        // remove all leading and trailing spaces from beg-end
        //consider:
            //std::string::substr()
            // std::string::find()
            // std::string::find_first_of()
            // std::string::erase()
            // std::stoul()
            // std::stod()
        Cheese(const std::string& desc); //receives m_desc
        
        // valid: return copy of current cheese with desired weight
        // else: return cheese object that is an empty state
        Cheese slice(size_t weight); //amount to slice off

        //set of queries
        auto getName()const->std::string;
        auto getWeight()const->size_t;
        auto getPrice()const->double;
        auto getDesc()const->std::string;

        //operator bool()const;
    };

    //free helper
    // |[Name;left;w21]|[weight; ;w5]|[price;fixed;precision2;w5]|[desc;right;w34]|\n
    auto operator<<(std::ostream& os, const Cheese& chez)->std::ostream&;

}
#endif //!SDDS_CHEESE_H