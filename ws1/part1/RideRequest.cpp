#include <iomanip>
#include "RideRequest.h"

using namespace std;
namespace sdds {

    // Define static member variable
    int RideRequest::displayCounter = 0;

    // Implement the constructor
    RideRequest::RideRequest() : price(0.0), hasDiscount(false) {
        customerName[0] = '\0';
        rideDescription[0] = '\0';
    }

    // Implement the read function
    void RideRequest::read(std::istream& is) {
        if (is.good()) {
            is.getline(customerName, 11, ',');
            is.getline(rideDescription, 26, ',');
            is >> price;
            char discountStatus;
            is >> discountStatus;
            hasDiscount = (discountStatus == 'Y');
            is.ignore(); // Consume the newline character
        }
    }

    // Implement the display function
    void RideRequest::display() const {
        if (customerName[0] == '\0') {
            cout << setw(2) << left << ++displayCounter << ". No Ride Request" << endl;
        }
        else {
            double priceWithTax = price * (1 + g_taxrate);
            double priceWithDiscount = hasDiscount ? priceWithTax * g_discount : priceWithTax;
            cout << setw(2) << left << ++displayCounter;
            cout << ". " << setw(10) << left << customerName;
            cout << "|" << setw(25) << left << rideDescription;
            cout << "|" << fixed << setprecision(2) << setw(12) << left << priceWithTax;
            if (hasDiscount) {
                cout << "|" << setw(13) << right << priceWithDiscount;
            }
            cout << endl;
        }
    }

} // namespace sdds
