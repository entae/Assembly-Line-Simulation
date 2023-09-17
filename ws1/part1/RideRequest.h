// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Sep 17, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

#include <iostream>
#include <istream>

namespace sdds {

    class RideRequest {
    private:
        char CUSTOMER_NAME[11];
        char RIDE_DESCRIPTION[26];
        double price;
        bool hasDiscount;

        static int displayCounter;

    public:
        RideRequest()=default;

        void read(std::istream& is);

        void display()const;
    };

} // namespace sdds

#endif // SDDS_RIDEREQUEST_H
