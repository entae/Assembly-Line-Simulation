// Name:                In Tae Chung
// Seneca Student ID:   128 958 220
// Seneca email:        itchung@myseneca.ca
// Date of completion:  Dec. 3, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "LineManager.h"
#include "Utilities.h"
#include "Workstation.h"

namespace sdds {
    LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stations) {

        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::ios_base::failure("Cannot open " + filename);
        }

        //start reading file line-by-line using extractToken()
        Utilities util;
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = 0;
            bool more = true;  // true if there is a next token
            std::string currToken = util.extractToken(line, pos, more); 

            // find current workstation in stations vector
            auto currStation = std::find_if(stations.begin(), stations.end(), [&currToken](const Workstation* station) {
                return station->getItemName() == currToken;
            });

            // extract next token and find matching workstation
            // then next station of currWorkstation is set as next workstation
            if (more) {
                std::string nextToken = util.extractToken(line, pos, more);
                auto nextStation = std::find_if(stations.begin(), stations.end(), [&nextToken](const Workstation* station) {
                    return station->getItemName() == nextToken;
                });
                (*currStation)->setNextStation(*nextStation);
            }

            // add each workstation to m_activeLine vector
            m_activeLine.push_back(*currStation);
        }

        // if m_firstStation is still null, link to last station in activeLine
        if (m_firstStation == nullptr && !m_activeLine.empty()) {
            m_firstStation = findLastInSequence(m_activeLine);
        }

        // set the number of customer orders
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
        for (auto station : m_activeLine) {
            station->fill(os);
        }
        for (auto station : m_activeLine) {
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

    void LineManager::display(std::ostream& os) const {
        for (auto station : m_activeLine) {
            station->display(os);
        }
    }

    Workstation* LineManager::findLastInSequence(const std::vector<Workstation*>& stations) {
        // lambda for checking if the nextStation within Workstation is nullptr
        auto lastStation = std::find_if(stations.begin(), stations.end(), [](const Workstation* station) {
            return station->getNextStation() == nullptr;
        });

        // if lastStation is not the end (if station was found), returns the station
        // otherwise nullptr
        return lastStation != stations.end() ? findPredecessor(stations, lastStation) : nullptr;
    }

    Workstation* LineManager::findPredecessor(const std::vector<Workstation*>& stations, std::vector<sdds::Workstation*>::const_iterator currStation) {
        // searches for checking if nextStation within Workstation is equal to currStation
        auto prevStation = std::find_if(stations.begin(), stations.end(), [currStation](const Workstation* station) {
            return station->getNextStation() == *currStation;
        });
        // if prevStation is equal to the end, then it return currStation
        // otherwise returns a recursive call to searchStations
        Workstation* result = (prevStation == stations.end()) ? *currStation : findPredecessor(stations, prevStation);
        return result;
    }

} // namespace sdds