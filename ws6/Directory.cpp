// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Nov 7, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iomanip>
#include "Directory.h"

namespace sdds {
    Directory::Directory(const std::string& name) {
        m_name = name;
    }

    Directory::~Directory() {
        for (Resource* resource : m_contents) {
            delete resource;
        }
        m_contents.clear();
    }

    void Directory::update_parent_path(const std::string& parent_path) {
        m_parent_path = parent_path;
        for (Resource* resource : m_contents) {
            resource->update_parent_path(path());
        }
    }

    NodeType Directory::type()const {
        return NodeType::DIR;
    }

    std::string Directory::path()const {
        return m_parent_path + m_name;
    }

    std::string Directory::name()const {
        return m_name;
    }

    int Directory::count()const {
        return static_cast<int>(m_contents.size());
    }

    size_t Directory::size()const {
        size_t size = 0;
        for (Resource* resource : m_contents) {
            size += resource->size();
        }
        return size;
    }

    Directory& Directory::operator+=(Resource* resource) {
        Resource* existingResource = find(resource->name());
        if (existingResource) {
            throw std::runtime_error("Resource with the same name already exists in the directory.");
        }
        m_contents.push_back(resource);
        resource->update_parent_path(path());
        return *this;
    }

    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) {
        Resource* result = nullptr;

        for (Resource* resource : m_contents) {
            if (resource->name() == name) {
                result = resource;
            }
        }
        // Custom loop to find OpFlags::RECURSIVE in the flags vector
        bool recursiveFlagFound = false;
        for (const OpFlags& flag : flags) {
            if (flag == OpFlags::RECURSIVE) {
                recursiveFlagFound = true;
            }
        }

        if (!result && recursiveFlagFound) {
            for (Resource* resource : m_contents) {
                if (resource->type() == NodeType::DIR) {
                    result = dynamic_cast<Directory*>(resource)->findRecursive(name, flags);
                }
            }
        }
        return result;
    }

    Resource* Directory::findRecursive(const std::string& name, const std::vector<OpFlags>& flags) const {
        Resource* result = nullptr;

        for (Resource* resource : m_contents) {
            if (resource->name() == name) {
                result = resource;
            }
            if (resource->type() == NodeType::DIR) {
                result = dynamic_cast<Directory*>(resource)->findRecursive(name, flags);
            }
        }
        return result;
    }

    void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags) {
        Resource* resToRemove = find(name, flags);
        if (!resToRemove) {
            throw std::invalid_argument(name + " does not exist in " + m_name + ".");
        }

        if (resToRemove->type() == NodeType::DIR) {
            bool recursiveFound = false;
            for (const OpFlags& flag : flags) {
                if (flag == OpFlags::RECURSIVE) {
                    recursiveFound = true;
                }
            }

            if (!recursiveFound) {
                throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
            }
        }

        m_contents.erase(std::remove(m_contents.begin(), m_contents.end(), resToRemove), m_contents.end());
        delete resToRemove;
    }

    void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const {
        os << "Total size: " << this->size() << " bytes" << std::endl;
        for (Resource* resource : m_contents) {
            if (resource->type() == NodeType::DIR) {
                os << "D";
            } else {
                os << "F";
            }
            os << " | " << std::left << std::setw(15) << resource->name() << " |";
            auto isRecursive = std::find_if(flags.begin(), flags.end(), [](FormatFlags flag) {
                return flag == FormatFlags::LONG;
            });
            if (isRecursive != flags.end()) {
                if (resource->type() == NodeType::DIR) {
                    os << std::right << " " << std::setw(2) << resource->count() << " | ";
                    os << std::right << std::setw(10) << std::to_string(resource->size()) + " bytes"
                    << " | ";
                } else {
                    os << std::right <<  " " << std::setw(2) << "  "
                    << " | ";
                    os << std::right << std::setw(10) << std::to_string(resource->size()) + " bytes"
                    << " | ";
                }
            }
            os << std::endl;
        }
    }

}  // namespace sdds
