// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 11, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iomanip>
#include "Cheese.h"

namespace sdds {

    Cheese::Cheese(const std::string &desc) {
        if (!desc.empty()) {
            //temp string to safely manipulate input string after removing lead/ending spaces
            size_t startPos = desc.find_first_not_of(" ");
            size_t endPos = desc.find_last_not_of(" ");
            std::string descCpy = desc.substr( startPos, (endPos - startPos + 1) );

            // m_name
            size_t comma = descCpy.find(',');
            m_name = descCpy.substr( 0, comma );
            if (comma != std::string::npos) descCpy.erase( 0, comma+1 );

            // m_weight
            comma = descCpy.find(',');
            m_weight = std::stoul( descCpy.substr( 0, comma ) );
            if (comma != std::string::npos) descCpy.erase( 0, comma+1 );

            // m_price
            comma = descCpy.find(',');
            m_price = std::stod( descCpy.substr( 0, comma ) );
            if (comma != std::string::npos) descCpy.erase( 0, comma+1 );

            // m_desc
            char target = ',';
            char replacement = ' ';
            for (size_t i = 0; i < descCpy.length(); ++i) {
                if (descCpy[i] == target) {
                    descCpy[i] = replacement;
                }
            }
            // Reduce consecutive spaces to a single space
            for ( size_t i = 0; i < descCpy.length() - 1; ++i) {
                if (descCpy[i] == ' ' && descCpy[i + 1] == ' ') {
                    size_t j = i + 1;
                    while (j < descCpy.length() && descCpy[j] == ' ') {
                        descCpy.erase(j, 1);
                    }
                }
            }
            m_desc = descCpy.substr( 0, descCpy.length() );

        } else {
            m_name = "";
            m_weight = 0;
            m_price = 0.0;
            m_desc = "";
        }
    }

    Cheese Cheese::slice(size_t weight){
        Cheese slicedCheese;
        if (weight <= m_weight) {
            slicedCheese = *this;
            slicedCheese.m_weight = weight;
            m_weight -= weight;
        } //else {
            //m_weight = 0;
        //}
        return slicedCheese;
    }

    auto Cheese::getName()const->std::string {
        return m_name;
    }
    auto Cheese::getWeight()const->size_t {
        return m_weight;
    }
    auto Cheese::getPrice()const->double {
        return m_price;
    }
    auto Cheese::getDesc()const->std::string {
        return m_desc;
    }

    // |[Name;left;w21]|[weight; ;w5]|[price;fixed;precision2;w5]|[desc;right;w34]|\n
    auto operator<<(std::ostream& os, const Cheese& chez)->std::ostream&  {
        os << '|';
        os.width(21);
        os << std::left << chez.getName() << '|';

        os.width(5);
        os << chez.getWeight() << '|';

        os.width(5);
        os << std::fixed << std::setprecision(2) << chez.getPrice() << '|';

        os.width(33);
        os << std::right << chez.getDesc() << " |" << std::endl;

        return os;
    }
}