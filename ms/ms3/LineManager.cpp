// Name:                In Tae Chung
// Seneca Student ID:   128 958 220
// Seneca email:        itchung@myseneca.ca
// Date of completion:  Dec. 3, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include <fstream>
#include <algorithm>

#include "LineManager.h"
#include "Utilities.h"
#include "Workstation.h"

namespace sdds {

LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    : m_activeLine(), m_cntCustomerOrder(0), m_firstStation(nullptr) {
    
    std::ifstream fs(file);
    if (!fs.is_open()) {
        throw std::ios_base::failure("Cannot open " + file);
    }

    Utilities util;
    std::string record;
    Workstation* previousStn = nullptr;

    while (std::getline(fs, record)) {
        size_t pos = 0;
            bool more = true;
            std::string currentToken = util.extractToken(record, pos, more);

            auto currentWorkstation = std::find_if(stations.begin(), stations.end(),
                [currentToken](const Workstation* station) {
                    return station->getItemName() == currentToken;
                });

            if (previousStn) {
                previousStn->setNextStation(*currentWorkstation);
            }
            else {
                m_firstStation = *currentWorkstation;
            }

            previousStn = *currentWorkstation;
            m_activeLine.push_back(previousStn);
        }

        if (m_firstStation == nullptr) {
            m_firstStation = stations.front();
        }

        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations() {
        m_activeLine.clear();
        Workstation* currStation = m_firstStation;
        while (currStation != nullptr) {
            m_activeLine.push_back(currStation);
            currStation = currStation->getNextStation();
        }
    }

    bool LineManager::run(std::ostream& os) {
        static size_t iteration = 0;
        os << "Line Manager Iteration: " << ++iteration << std::endl;
        size_t oldSz = g_completed.size();

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (Workstation* station : m_activeLine) {
            station->fill(os);
        }

        for (Workstation* station : m_activeLine) {
            station->attemptToMoveOrder();
        }

        size_t completedIteration = g_completed.size() - oldSz;
        if (completedIteration > 1) {
            for (size_t i = 0; i < completedIteration / 2; i++) {
                size_t indexA = oldSz + i;
                size_t indexB = g_completed.size() - 1 - i;
                std::swap(g_completed[indexA], g_completed[indexB]);
            }
        }

        return g_pending.empty() && g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }


    void LineManager::display(std::ostream& os)const {
        for (Workstation* station : m_activeLine) {
            station->display(os);
        }
    }

}
