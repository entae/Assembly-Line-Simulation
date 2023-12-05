// Name:                In Tae Chung
// Seneca Student ID:   128 958 220
// Seneca email:        itchung@myseneca.ca
// Date of completion:  Dec. 3, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <iostream>
#include <vector>
#include "Workstation.h"

namespace sdds {

    class LineManager {
        std::vector<Workstation*> m_activeLine{};
        size_t m_cntCustomerOrder{};
        Workstation* m_firstStation{};

    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };

}

#endif // !SDDS_LINEMANAGER_H
