// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Nov 7, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include <iostream>
#include <string>
#include "Resource.h"
#include "Flags.h"

namespace sdds
{
    class File : public Resource {
    private:
        /* Resource Attributes:
        std::string m_name{}; 
            // Stores the name of the resource
        std::string m_parent_path = "/"; 
            // Stores the absolute path of the folder where the resource is located
        */
        std::string m_contents{}; //stores contents of a file
    
    public:
        File()=default;
        File(const std::string& name, const std::string& contents = "");

        virtual void update_parent_path(const std::string& parent_path);
        virtual std::string name()const;
        virtual int count()const;
        virtual std::string path()const;
        virtual size_t size()const;
        virtual NodeType type()const;
        virtual ~File()=default;
    };

}

#endif