#include "CovidCollection.h"

#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <numeric>

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
            cc_collection.push_back(covid);
        }
    }

    void CovidCollection::display(std::ostream& out, const std::string& country) const {
        auto displayFunc = [&out](const Covid& c) {
            out << c << std::endl;
        };

        // Calculate and print total cases and deaths
        unsigned int totalCases = std::accumulate(cc_collection.begin(), cc_collection.end(), 0,
            [](unsigned int sum, const Covid& c) {
                return sum + c.c_cases;
            });

        unsigned int totalDeaths = std::accumulate(cc_collection.begin(), cc_collection.end(), 0,
            [](unsigned int sum, const Covid& c) {
                return sum + c.c_deaths;
            });

        if (country == "ALL") {
            std::for_each(cc_collection.begin(), cc_collection.end(), displayFunc);

            out << "| " << std::right << std::setw(79) << "Total cases around the world: " << totalCases << " |" << std::endl;
            out << "| " << std::right << std::setw(79) << "Total deaths around the world: " << totalDeaths << " |" << std::endl;
        } else {
            out << "Displaying information of country = " << country << std::endl;

            auto countryFilter = [country](const Covid& c) {
                return trim(c.c_country) == trim(country);
            };

            std::vector<Covid> filteredCollection;
            std::copy_if(cc_collection.begin(), cc_collection.end(), std::back_inserter(filteredCollection),
                [country](const Covid& c) {
                    return trim(c.c_country) == trim(country);
                });
            
            std::for_each(filteredCollection.begin(), filteredCollection.end(), displayFunc);

            // Calculate and print country-specific information
            unsigned int countryTotalCases = std::accumulate(filteredCollection.begin(), filteredCollection.end(), 0,
                [](unsigned int sum, const Covid& c) {
                    return sum + c.c_cases;
                });

            unsigned int countryTotalDeaths = std::accumulate(filteredCollection.begin(), filteredCollection.end(), 0,
                [](unsigned int sum, const Covid& c) {
                    return sum + c.c_deaths;
                });

            // Calculate percentages once
            double casesPercentage = static_cast<double>(countryTotalCases) / totalCases * 100;
            double deathsPercentage = static_cast<double>(countryTotalDeaths) / totalDeaths * 100;

            // Determine the width based on the condition
            int width = (casesPercentage >= 10 && deathsPercentage >= 10) ? 27 :
                        (casesPercentage >= 10 || deathsPercentage >= 10) ? 28 : 29;

            // Adjust the width based on the length of the trimmed country name
            width -= (trim(country).length() - country.length() + 6);

            out << "----------------------------------------------------------------------------------------" << std::endl;
            out << "| " << std::right << std::setw(78 - country.length()) << "Total cases in " << country << ": " << countryTotalCases << " |" << std::endl;
            out << "| " << std::right << std::setw(78 - country.length()) << "Total deaths in " << country << ": " << countryTotalDeaths << " |" << std::endl;
            out << "| " << std::right << std::setw(width) << country << " has " 
                << std::fixed << std::setprecision(6) << casesPercentage << "% of global cases " 
                << "and " << std::fixed << std::setprecision(6) << deathsPercentage << "% of global deaths |" << std::endl;

        }
    }

    void CovidCollection::sort(const std::string& field) {
        std::sort(cc_collection.begin(), cc_collection.end(), [field](const Covid& a, const Covid& b) {
            if (field == "country") {
                return a.c_country < b.c_country || (a.c_country == b.c_country && a.c_deaths < b.c_deaths);
            } else if (field == "city") {
                return a.c_city < b.c_city || (a.c_city == b.c_city && a.c_deaths < b.c_deaths);
            } else if (field == "variant") {
                return a.c_variant < b.c_variant || (a.c_variant == b.c_variant && a.c_deaths < b.c_deaths);
            } else if (field == "year") {
                return a.c_year < b.c_year || (a.c_year == b.c_year && a.c_deaths < b.c_deaths);
            } else if (field == "cases") {
                return a.c_cases < b.c_cases || (a.c_cases == b.c_cases && a.c_deaths < b.c_deaths);
            } else if (field == "deaths") {
                return a.c_deaths < b.c_deaths || (a.c_deaths == b.c_deaths && a.c_country < b.c_country);
            } else {
                // Default case: sort by country
                return a.c_country < b.c_country || (a.c_country == b.c_country && a.c_deaths < b.c_deaths);
            }
        });
    }

    bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const {
        return std::any_of(cc_collection.begin(), cc_collection.end(), 
            [variant, country, deaths](const Covid& c) {
                return c.c_variant == variant && c.c_country == country && c.c_deaths > deaths;
            });
    }

    std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const {
        std::list<Covid> result;
        std::copy_if(cc_collection.begin(), cc_collection.end(), std::back_inserter(result),
            [deaths](const Covid& c) {
                return c.c_deaths >= deaths;
            });
        return result;
    }

    void CovidCollection::updateStatus() {
        std::transform(cc_collection.begin(), cc_collection.end(), cc_collection.begin(), [](Covid& c) {
            if (c.c_deaths > 300) {
                c.c_severity = "EPIDEMIC";
            } else if (c.c_deaths < 50) {
                c.c_severity = "EARLY";
            } else {
                c.c_severity = "MILD";
            }
            return c;
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
            << " | " << std::setw(3) << std::right << theCovid.c_deaths
             << " | | " << std::setw(8) << std::right << theCovid.c_severity << " |";

        return out;
    }


    std::string CovidCollection::trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

} // namespace sdds