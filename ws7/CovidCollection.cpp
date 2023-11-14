#include "CovidCollection.h"
#include <iomanip>
#include <stdexcept>

namespace sdds {

    CovidCollection::CovidCollection(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::invalid_argument("Error: Unable to open file");
        }

        // Read data from the file and populate the collection
        std::string line;
        while (std::getline(file, line)) {
            Covid covid;
            covid.c_country = trim(line.substr(0, 25));
            covid.c_city = trim(line.substr(25, 25));
            covid.c_variant = trim(line.substr(50, 25));
            covid.c_year = std::stoi(trim(line.substr(75, 5)));
            covid.c_cases = std::stoi(trim(line.substr(80, 5)));
            covid.c_deaths = std::stoi(trim(line.substr(85, 5)));
            collection.push_back(covid);
        }
    }

    // DO NOT USE MANUAL LOOPS
    void CovidCollection::display(std::ostream& out) const {
        std::for_each(collection.begin(), collection.end(), [&out](const Covid& c) {
            out << c;
        });
    }

    std::ostream& operator<<(std::ostream& out, const Covid& theCovid) {
        out << "| " << std::setw(21) << std::left << theCovid.c_country
            << " | " << std::setw(15) << std::left << theCovid.c_city
            << " | " << std::setw(20) << std::left << theCovid.c_variant;
        if (theCovid.c_year >= 0) {
            out << " | " << std::setw(6) << std::right << theCovid.c_year;
        } else {
            // Output a blank if c_year is less than 0
            out << " | " << std::setw(6) << std::right << " ";
        }
        out << " | " << std::setw(4) << std::right << theCovid.c_cases
            << " | " << std::setw(3) << std::right << theCovid.c_deaths << " |" << std::endl;
        return out;
    }


    std::string CovidCollection::trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

} // namespace sdds
