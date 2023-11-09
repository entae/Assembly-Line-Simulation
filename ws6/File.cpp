// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Nov 7, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <string>
#include "Resource.h"
#include "Flags.h"  // Include the Flags header
#include "File.h"

namespace sdds {

    File::File(const std::string& name, const std::string& contents) {
        m_name = name;
        m_contents = contents;
    }

    void File::update_parent_path(const std::string& parent_path) {
        m_parent_path = parent_path;
    }

    NodeType File::type()const {
        return NodeType::FILE;  // Use the NodeType enum to indicate it's a file
    }

    std::string File::path() const {
        return m_parent_path + m_name;
    }


    std::string File::name()const {
        return m_name;
    }

    int File::count()const {
        return -1;
    }

    size_t File::size()const {
        return m_contents.size();
    }

}  // namespace sdds
