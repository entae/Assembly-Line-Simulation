// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Sep 27, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <fstream>
#include <string>
#include "AirportModels.h"
#include "Timer.h"

namespace sdds
{
    // Airport class
    std::ostream& Airport::formatLabel( std::ostream& os)
    {
        os << std::right;
        os.width(23);
        os.fill('.');

        return os;
    }

    std::ostream& Airport::formatValue( std::ostream& os)
    {
        os << std::left;
        os.width(30);
        os.fill('.');

        return os;
    }

    std::ostream& operator<<( std::ostream& os, const Airport& A )
    {
        if ( A.m_code.empty() )
        {
            os << "Empty Airport";
        }
        else
        {
            Airport::formatLabel(os) << "Airport Code : ";
            Airport::formatValue(os) << A.m_code << '\n';

            Airport::formatLabel(os) << "Airport Name : ";
            Airport::formatValue(os) << A.m_name << '\n';

            Airport::formatLabel(os) << "City : ";
            Airport::formatValue(os) << A.m_city << '\n';

            Airport::formatLabel(os) << "State : ";
            Airport::formatValue(os) << A.m_state << '\n';

            Airport::formatLabel(os) << "Country : ";
            Airport::formatValue(os) << A.m_country << '\n';
            // may need to set precision / format lat+long
            Airport::formatLabel(os) << "Latitude : ";
            Airport::formatValue(os) << A.m_lat << '\n';

            Airport::formatLabel(os) << "Longitude : ";
            Airport::formatValue(os) << A.m_long << '\n';
        }
        return os;
    }

    // AirportLog Class
    AirportLog::AirportLog(const char* filename) : m_airports(nullptr), m_count(0) {
        std::ifstream file(filename);
        std::string line{};

        if (file) {
            getline(file, line);
            while (getline(file, line)) m_count++;

            file.clear();
            file.seekg(0, std::ios::beg);

            m_airports = new Airport[m_count];

            size_t idx = 0;
            getline(file, line);
            for (size_t i = 0; i < m_count; i++) {
                getline(file, m_airports[idx].m_code, ',');
                getline(file, m_airports[idx].m_name, ',');
                getline(file, m_airports[idx].m_city, ',');
                getline(file, m_airports[idx].m_state, ',');
                getline(file, m_airports[idx].m_country, ',');

                std::string lat_s{}, lng_s{};
                getline(file, lat_s, ',');
                getline(file, lng_s);

                try {
                    m_airports[idx].m_lat = std::stod(lat_s);
                    m_airports[idx].m_long = std::stod(lng_s);
                }
                catch (const std::invalid_argument& e) {
                }
                idx++;
            }
        }
    }

    // rule of 5
    AirportLog::~AirportLog()
    {
        delete[] m_airports;
    }

    AirportLog::AirportLog(const AirportLog &AL)
    {
        *this = AL;
    }

    AirportLog &AirportLog::operator=(const AirportLog &AL)
    {
        if (this != &AL) {
            delete[] m_airports;

            m_count = AL.m_count;
            
            if(AL.m_airports) {
                m_airports = new Airport[m_count];
                for (size_t i = 0; i < m_count; i++) {
                    m_airports[i] = AL.m_airports[i];
                }
            }
            else {
                m_airports = nullptr;
            }
        }
        return *this;
    }
    
    // implement Move constructor & assignment
    AirportLog::AirportLog(AirportLog &&AL)
    {
        // m_count = AL.m_count;
        // m_airports = AL.m_airports;

        // // Reset the source object
        // AL.m_count = 0;
        // AL.m_airports = nullptr;
        *this = std::move(AL);
    }

    AirportLog &AirportLog::operator=(AirportLog &&AL)
    {
        if (this != &AL) {
            delete[] m_airports; // Release any previously allocated memory

            m_count = AL.m_count;
            m_airports = AL.m_airports;

            // Reset the source object
            AL.m_count = 0;
            AL.m_airports = nullptr;
        }
        return *this;
    }

    void AirportLog::addAirport(const Airport &A)
    {
        Airport* temp = new Airport[ m_count + 1 ];
        for (size_t i = 0; i < m_count; i++) {
            temp[i] = m_airports[i];
        }
        temp[m_count] = A;

        delete[] m_airports;
        m_airports = temp;
        m_count++;
    }

    AirportLog AirportLog::findAirport(const char *state, const char *country)const
    {
        AirportLog result;
        for (size_t i = 0; i < m_count; i++) {
            if (m_airports[i].m_state == state && m_airports[i].m_country == country) {
            result.addAirport(m_airports[i]);
            }
            // if(strcmp(m_airports[i].m_state.c_str(), state) == 0 && strcmp(m_airports[i].m_country.c_str(), country) ==0) {
            //     result.addAirport(m_airports[i]);
            // }
        }
        return result; //*this;
    }

//reduce to one return
    const Airport &AirportLog::operator[](size_t index) const
    {
        if (index < static_cast<size_t>(m_count)) {
            return m_airports[index];
        } else {
            // Return an empty Airport if the index is not valid
            static Airport emptyAirport;
            return emptyAirport;
        }
    }

    AirportLog::operator size_t() const
    {
        return static_cast<size_t>(m_count);
    }
}