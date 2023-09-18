// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Sep 17, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

namespace sdds {

    class RideRequest {
    private:
        char CUSTOMER_NAME[11];
        char* RIDE_DESCRIPTION[26];
        double m_price;
        bool m_discount;

    public:
        //default constructor
        RideRequest();
        ~RideRequest();
        void read(std::istream& is);
        void display()const;
    };

} // namespace sdds

extern double g_taxrate;
extern double g_discount;

#endif // SDDS_RIDEREQUEST_H
