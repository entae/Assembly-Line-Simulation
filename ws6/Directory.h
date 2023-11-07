// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Nov 7, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include <vector>
#include "Resource.h"
#include "Flags.h"

namespace sdds {
    class Directory : public Resource {
    private:
        std::vector<Resource*> m_contents;

    public:
        Directory()=default;
        Directory(const std::string& name); 
        // Custom constructor
        
        virtual void update_parent_path(const std::string& parent_path);
        virtual std::string name()const;
        virtual int count()const;
        virtual std::string path()const;
        virtual size_t size()const;
        virtual NodeType type()const;
        virtual ~Directory(); 
        // Destructor to deallocate memory for each resource that this dir holds

        Directory& operator+=(Resource* resource);

        Resource* find(const std::string& name, const std::vector<OpFlags>& flags = {});
        

    private:
        // Private helper function to recursively find a resource by name
        Resource* findRecursive(const std::string& name, const std::vector<OpFlags>& flags) const;
        
        // Make the class non-copyable and non-movable
        Directory(const Directory& other)=delete;
        Directory& operator=(const Directory& other)=delete;
        Directory(Directory&& other)=delete;
        Directory& operator=(Directory&& other)=delete;
    };
}  // namespace sdds

#endif
