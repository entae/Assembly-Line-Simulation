// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Sep 17, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <iomanip>
#include <cstring>
#include "RideRequest.h"

//extern variables
double g_taxrate = 0.0;
double g_discount = 0.0;

using namespace std;
namespace sdds {

    RideRequest::RideRequest() {
        CUSTOMER_NAME[0] = '\0';
        RIDE_DESCRIPTION = nullptr;
        m_price = 0.0;
        m_discount = false;
    }

    RideRequest::~RideRequest() {
        delete[] RIDE_DESCRIPTION;
    }
    
    void RideRequest::read(std::istream& is) {
        if (is) {
            char temp[50]; //temp buffer
            is.getline(temp, 11, ',');
            strncpy(CUSTOMER_NAME, temp, 10);
            CUSTOMER_NAME[10] = '\0';
            // is.getline(CUSTOMER_NAME, 11, ',');

            is.getline(temp, 26, ',');
            strncpy(RIDE_DESCRIPTION, temp, 25);
            RIDE_DESCRIPTION[25] = '\0';
            // is.getline(RIDE_DESCRIPTION, 26, ',');

            is >> m_price;
            //is.ignore(); //skipping comma
            char discountStatus;
            is >> discountStatus;
            m_discount = (discountStatus == 'Y');
            //is.ignore(); //skipping newline
        }
    }

    void RideRequest::display()const {
        //function scope variable
        static int COUNTER = 0;

        cout << setw(2) << left << ++COUNTER << ". ";

        if (CUSTOMER_NAME[0] == '\0') {
            cout << "No Ride Request" << endl;
        }
        else {
            double PRICE_WITH_TAX = ( m_price + (m_price * g_taxrate) );

            cout << setw(10) << left << CUSTOMER_NAME << '|';
            cout << setw(25) << left << RIDE_DESCRIPTION << '|';
            cout << fixed << setprecision(2) << setw(12) << left << PRICE_WITH_TAX << "|";

            if (m_discount) {
                double PRICE_WITH_DISCOUNT = ( PRICE_WITH_TAX - (PRICE_WITH_TAX * g_discount) );
                // PRICE_WITH_TAX = (int)( (PRICE_WITH_TAX + 0.005) * 100 ) / 100.0;
                cout << setw(13) << right << fixed << setprecision(2) << PRICE_WITH_DISCOUNT;
            }
            cout << endl;
        }
    }

} // namespace sdds
