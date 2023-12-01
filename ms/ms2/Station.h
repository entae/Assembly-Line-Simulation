// Name:                In Tae Chung
// Seneca Student ID:   128 958 220
// Seneca email:        itchung@myseneca.ca
// Date of completion:  Nov. 19, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>
#include <string>

namespace sdds {

    class Station {
        int m_id{};
        std::string m_itemName{};
        std::string m_description{};
        size_t m_serialNumber{};
        size_t m_quantity{};

    public:
        static size_t m_widthField;
        static size_t id_generator;

        Station(const std::string& record);

        const std::string& getItemName()const;

        size_t getNextSerialNumber();

        size_t getQuantity()const;

        void updateQuantity();

        void display(std::ostream& os, bool full)const;
    };

}

#endif //!SDDS_STATION_H
