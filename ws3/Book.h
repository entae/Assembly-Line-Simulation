// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Oct 1, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>
#include <string>

namespace sdds {

    class Book {
        std::string m_title{}; // valid = !null || !empty
        unsigned m_numChapters{}; // valid = chapters > 0
        unsigned m_numPages{}; // valid = page > 0
        //when valid, print as:
        // title+chapters+pages (right + 56 char) | (avg pages per chapter) (left + 15 char)
    public:
        Book();
        Book(const std::string& title, unsigned numChapters, unsigned numPages);
        
        // TODO: In completing Part 1, add here the missing 
        // member prototypes that would be necessary for the 
        // Collection module code and tester module w3_p1.cpp 
        // to manage Book-type objects. 
        operator bool()const;

        // In completing Part 2, add here the missing 
        // member prototypes that would be necessary for 
        // OrderedCollection module code and tester module 
        // w3_p2.cpp to manage Book-type object. 
        bool operator<(const Book& RO)const;
        bool operator>(const Book& RO)const;
        ~Book() = default;
        // Write the implementations of these functions 
        // in Book.cpp file

        std::ostream& print(std::ostream& os) const;
        
    };

    std::ostream& operator<<(std::ostream& os, const Book& book);

}

#endif // !SDDS_BOOK_H