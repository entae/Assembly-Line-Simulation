// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 18, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>
#include <string>

namespace sdds {

    //holds info about single book
    class Book {
        std::string m_author{};
        std::string m_title{};
        std::string m_country{};
        size_t m_year{};
        double m_price{};
        std::string m_desc{};
    public:
        Book()=default;
        //receives reference to unmodifiable string
        //receives formatted string to extract and parse
        Book(const std::string& strBook);
        // std::string trimSpaces(const std::string& str);
        //queries 
        const std::string& title()const;
        const std::string& country()const;
        const size_t& year()const;

        //returns price by reference
        double& price();
        bool isEmpty()const;
        
        void display(std::ostream& os)const;
    };

    std::ostream& operator<<(std::ostream& os, const Book& book);

}

#endif //!SDDS_BOOK_H