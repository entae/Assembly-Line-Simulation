// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Sep 27, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>

namespace sdds {

    // handles data about a single airport
    struct Airport {
        std::string m_code{};
        std::string m_name{};
        std::string m_city{};
        std::string m_state{};
        std::string m_country{};
        double m_lat{0.0};
        double m_long{0.0};
        static std::ostream& formatLabel( std::ostream& os);
        static std::ostream& formatValue( std::ostream& os);
    };
    std::ostream& operator<<( std::ostream& os, const Airport& A ); 

    //manages a collection of Airports
    class AirportLog {
        Airport* m_airports{};  // dynamic array of airports
        size_t m_count{0};      // num of airports in array

    public:
        AirportLog()=default;
        AirportLog(const char* filename );
        // rule of 5
        virtual ~AirportLog();
        AirportLog( const AirportLog& AL );
        AirportLog& operator=( const AirportLog& AL );
        // implement Move constructor & assignment
        AirportLog( AirportLog&& AL );
        AirportLog& operator=( AirportLog&& AL );

        void addAirport( const Airport& A );
        AirportLog findAirport( const char* state, const char* country )const;
        
        const Airport& operator[]( size_t index )const;
        operator size_t()const;
    };
}

#endif // !SDDS_AIRPORTMODELS_H