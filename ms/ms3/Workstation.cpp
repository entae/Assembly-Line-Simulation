// Name:                In Tae Chung
// Seneca Student ID:   128 958 220
// Seneca email:        itchung@myseneca.ca
// Date of completion:  Dec. 3, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

namespace sdds {

    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};

    Workstation::Workstation(const std::string& record) : Station(record), m_pNextStation(nullptr) {}

    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) m_orders.front().fillItem(*this, os);
    }

    bool Workstation::attemptToMoveOrder() {
        bool orderMoved = false;
        if (!m_orders.empty()) {
            CustomerOrder& order = m_orders.front();
            if (order.isOrderFilled()) {
                g_completed.push_back(std::move(order));
                m_orders.pop_front();
                orderMoved = true;
            }
            else if (!order.isItemFilled(getItemName()) && getQuantity() > 0) {
                orderMoved = false;
            }
            else if (m_pNextStation) {
                *m_pNextStation += std::move(order);
                m_orders.pop_front();
                orderMoved = true;
            }
            else {
                g_incomplete.push_back(std::move(order));
                m_orders.pop_front();
                orderMoved = true;
            }
        }
        return orderMoved;
    }

    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const {
        os << getItemName() << " --> ";
        if (m_pNextStation) {
            os << m_pNextStation->getItemName();
        }
        else {
            os << "End of Line";
        }
        os << std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }

}
