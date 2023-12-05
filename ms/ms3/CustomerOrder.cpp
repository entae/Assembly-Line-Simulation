// Name:                In Tae Chung
// Seneca Student ID:   128 958 220
// Seneca email:        itchung@myseneca.ca
// Date of completion:  Dec. 1, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include <vector>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"

namespace sdds {
    //initialize class/static attribute
    size_t CustomerOrder::m_widthField = 1;

    // 1-argument constructor
    CustomerOrder::CustomerOrder(const std::string& record) {
        Utilities util;
        std::vector<std::string> tokens;
        size_t pos = 0;
        bool more = false;

        // Extract all tokens from string
        do {
            tokens.push_back(util.extractToken(record, pos, more));
        } while (more);

        // Set the item count to be equal to the number of tokens minus customer and product name
        m_cntItem = tokens.size() - 2;

        // Initialize the list of 'Item' dynamically
        m_lstItem = new Item*[m_cntItem];

        // Populate the object with tokens
        for (size_t x = 0; x < tokens.size(); x++) {
            // name of the customer
            if (x == 0) {
                m_name = tokens[x];
            }
            // name of the product
            else if (x == 1) {
                m_product = tokens[x];
            }
            // pieces to be assembled
            else {
                m_lstItem[x - 2] = new Item(tokens[x]);
            }
        }

        // Set the field width to max between CustomerOrder::m_widthField or Utilities::m_widthField
        m_widthField = (m_widthField > util.getFieldWidth()) ? m_widthField : util.getFieldWidth();
    }

    CustomerOrder::CustomerOrder(const CustomerOrder&) {
        throw std::string("ERROR: cannot copy CustomerOrder");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
        *this = std::move(src);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this != &src) {
            // Release existing resources
            for (size_t i = 0; i < m_cntItem; i++) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            // Move resources from src to this
            m_name = std::move(src.m_name);
            m_product = std::move(src.m_product);
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;

            // Reset src
            src.m_cntItem = 0;
            src.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        bool itemFilled = false;

        for (size_t i = 0; i < m_cntItem && !itemFilled; i++) {
            if (!m_lstItem[i]->m_isFilled && station.getItemName() == m_lstItem[i]->m_itemName) {
                if (station.getQuantity() > 0) {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
                    itemFilled = true;
                } else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++) {
            os << std::right << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
                << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
            if (m_lstItem[i]->m_isFilled) {
                os << "FILLED";
            } else {
                os << "TO BE FILLED";
            }
            os << std::endl;
        }
    }

    void CustomerOrder::setWidthField(size_t width) {
        m_widthField = width;
    }

}