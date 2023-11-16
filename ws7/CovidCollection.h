#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

// DO NOT USE MANUAL LOOPS == should not use "for" or "while"
namespace sdds {

    struct Covid {
        std::string c_country{};
        std::string c_city{};
        std::string c_variant{};
        int c_year{};
        unsigned int c_cases{};
        unsigned int c_deaths{};
         // this field fills 8 characters when printed
        std::string c_severity{"General"};
    };

    class CovidCollection {
        std::vector<Covid> cc_collection{};

        // Helper function to trim whitespace from the beginning and end of a string
        static std::string trim(const std::string& str);

    public:
        CovidCollection(const std::string& filename);

        // Task #1 DO NOT USE MANUAL LOOPS
        void display(std::ostream& out, const std::string& country = "ALL")const;
        // Task #2 DO NOT USE MANUAL LOOPS
        void sort(const std::string& field = "country");
        // Task #3 DO NOT USE MANUAL LOOPS
        bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths)const;
        // Task #4 DO NOT USE MANUAL LOOPS
        std::list<Covid> getListForDeaths(unsigned int deaths)const;
        // Task #5 DO NOT USE MANUAL LOOPS
        void updateStatus();
    };

    // Free Helper
    std::ostream& operator<<(std::ostream& out, const Covid& theCovid);

} // namespace sdds

#endif