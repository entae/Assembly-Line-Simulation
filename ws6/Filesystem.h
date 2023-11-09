// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Nov 8, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include "Resource.h"
#include "Flags.h"
#include "Directory.h"

namespace sdds
{
    class Filesystem {
    private:
        Directory* m_root{};
        Directory* m_current{};

        std::vector<std::string> split(std::string str, const char delim);
        std::string trimSpaces(std::string str);
    public:
        Filesystem()=default;
        Filesystem(const std::string filename, const std::string rootName = "");
        ~Filesystem();

        Filesystem& operator+=(Resource* resource);
        Directory* change_directory(const std::string& dirName = "");
        Directory* get_current_directory() const;

        // move operations
        Filesystem(Filesystem&& other);
        Filesystem& operator=(Filesystem&& other);
        // copy operations now allowed
        Filesystem(const Filesystem& other) = delete;
        Filesystem& operator=(const Filesystem& other) = delete;

    };

}

#endif