// Name:                In Tae Chung
// Seneca Student ID:   128 958 220
// Seneca email:        itchung@myseneca.ca
// Date of completion:  Dec. 1, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <iostream>
#include "Station.h"

namespace sdds {

    class CustomerOrder {
        // Item struct
        struct Item {
            std::string m_itemName{};
            size_t m_serialNumber{ 0 };
            bool m_isFilled{ false };

            Item(const std::string& src) : m_itemName(src) {};
        };

        // CustomerOrder attributes
        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{};
        Item** m_lstItem{};

        //class attribute
        static size_t m_widthField;

    public:
        CustomerOrder()=default;
        CustomerOrder(const std::string& record);

        CustomerOrder(const CustomerOrder&);
        CustomerOrder& operator=(const CustomerOrder&) = delete;

        CustomerOrder(CustomerOrder&&) noexcept;
        CustomerOrder& operator=(CustomerOrder&&) noexcept;

        ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;

        static void setWidthField(size_t width);
    };

}

#endif // !SDDS_CUSTOMERORDER_H
