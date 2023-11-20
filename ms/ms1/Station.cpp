// Name:                In Tae Chung
// Seneca Student ID:   128 958 220
// Seneca email:        itchung@myseneca.ca
// Date of completion:  Nov. 19, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>

#include "Station.h"
#include "Utilities.h"

namespace sdds {

    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;

    Station::Station(const std::string& record) : m_id(++id_generator), m_serialNumber(0), m_quantity(0) {
        Utilities util;
        size_t nextPos = 0;
        bool moreTokens = true;

        // Extract tokens from the record
        m_itemName = util.extractToken(record, nextPos, moreTokens);
        m_serialNumber = std::stoi(util.extractToken(record, nextPos, moreTokens));
        m_quantity = std::stoi(util.extractToken(record, nextPos, moreTokens));
        m_description = util.extractToken(record, nextPos, moreTokens);

        // Update Station::m_widthField and Utilities::m_widthField
        if (m_itemName.length() > m_widthField) {
            m_widthField = m_itemName.length();
        }
    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0) {
            --m_quantity;
        }
    }

    void Station::display(std::ostream& os, bool full) const {
        os << std::setw(3) << std::setfill('0') << std::right << m_id << " | " 
            << std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName << " | " 
            << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";

        if (full) {
            os << std::setw(4) << std::right << m_quantity << " | " 
                << std::left << m_description;
        }

        os << std::endl;
    }


}