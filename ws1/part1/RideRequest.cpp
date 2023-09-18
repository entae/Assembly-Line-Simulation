// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Sep 17, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <iomanip>
#include "RideRequest.h"

using namespace std;
namespace sdds {

    double g_taxrate = 0.0;
    double g_discount = 0.0;

    RideRequest::~RideRequest() {
        delete[] RIDE_DESCRIPTION;
    }
    
    void RideRequest::read(std::istream& is) {
        if (is) {
            is.getline(CUSTOMER_NAME, 11, ',');
            is.getline(RIDE_DESCRIPTION, 26, ',');
            is >> m_price;
            char discountStatus;
            is >> discountStatus;
            m_discount = (discountStatus == 'Y');
        }
    }

    void RideRequest::display() const {
        static int COUNTER = 0;
        cout << setw(2) << left << ++COUNTER << ". ";       
        if (CUSTOMER_NAME[0] == '\0') {
            cout << "No Ride Request" << endl;
        }
        else {
            double PRICE_WITH_TAX = ( m_price + (m_price * g_taxrate) );
            double PRICE_WITH_DISCOUNT = ( PRICE_WITH_TAX - (PRICE_WITH_TAX * g_discount) );
            cout << ". " << setw(10) << left << CUSTOMER_NAME << '|';
            cout << setw(25) << left << RIDE_DESCRIPTION << '|';
            cout << fixed << setprecision(2) << setw(12) << left << PRICE_WITH_TAX << "|";
            if (m_discount) {
                cout << setw(13) << right << PRICE_WITH_DISCOUNT;
            }
            cout << endl;
        }
    }

} // namespace sdds
