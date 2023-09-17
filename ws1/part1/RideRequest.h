#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

#include <iostream>
#include <istream>

namespace sdds {

    class RideRequest {
    private:
        char customerName[11];
        char rideDescription[26];
        double price;
        bool hasDiscount;

        static int displayCounter;

    public:
        RideRequest();

        void read(std::istream& is);

        void display() const;
    };

} // namespace sdds

    // Declare global variables for tax rate and discount as extern
    extern double g_taxrate;
    extern double g_discount;

#endif // SDDS_RIDEREQUEST_H
