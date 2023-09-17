// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Sep 17, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iomanip>
#include "RideRequest.h"

using namespace std;
namespace sdds {

    //externed variables
    double g_discount = 0.0;
    double g_taxrate = 0.0;

    // Implement the read function
    void RideRequest::read(std::istream& is) {
        if (is.good()) {
            is.getline(CUSTOMER_NAME, 11, ',');
            is.getline(RIDE_DESCRIPTION, 26, ',');
            is >> price;
            char discountStatus;
            is >> discountStatus;
            hasDiscount = (discountStatus == 'Y');
            is.ignore(); // Consume the newline character
        }
    }

    // Implement the display function
    void RideRequest::display() const {
        static int COUNTER = 0;
        if (CUSTOMER_NAME[0] == '\0') {
            cout << setw(2) << left << ++COUNTER << ". No Ride Request" << endl;
        }
        else {
            double PRICE_WITH_TAX = price * (1 + g_taxrate);
            double PRICE_WITH_DISCOUNT = hasDiscount ? PRICE_WITH_TAX * g_discount : PRICE_WITH_TAX;
            cout << setw(2) << left << ++COUNTER;
            cout << ". " << setw(10) << left << CUSTOMER_NAME;
            cout << "|" << setw(25) << left << RIDE_DESCRIPTION;
            cout << "|" << fixed << setprecision(2) << setw(12) << left << PRICE_WITH_TAX;
            if (hasDiscount) {
                cout << "|" << setw(13) << right << PRICE_WITH_DISCOUNT;
            }
            cout << endl;
        }
    }

} // namespace sdds
