#ifndef COVID_COLLECTION_H
#define COVID_COLLECTION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace sdds {

    struct Covid {
        std::string c_country;
        std::string c_city;
        std::string c_variant;
        int c_year;
        unsigned int c_cases;
        unsigned int c_deaths;
    };

    class CovidCollection {
        std::vector<Covid> collection;

        // Helper function to trim whitespace from the beginning and end of a string
        static std::string trim(const std::string& str);

    public:
        CovidCollection(const std::string& filename);

        // DO NOT USE MANUAL LOOPS
        void display(std::ostream& out) const;
    };

    // Free Helper
    std::ostream& operator<<(std::ostream& out, const Covid& theCovid);

} // namespace sdds

#endif // COVID_COLLECTION_H
