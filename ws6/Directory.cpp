// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Nov 7, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Directory.h"

namespace sdds {
    Directory::Directory(const std::string& name) {
        m_name = name;
    }

    Directory::~Directory() {
        for (Resource* resource : m_contents) {
            delete resource;
        }
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
        return (m_parent_path == "/") ? ("/" + m_name) : (m_parent_path + "/" + m_name);
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
                break;
            }
        }

        if (!result && std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end()) {
            for (Resource* resource : m_contents) {
                if (resource->type() == NodeType::DIR) {
                    result = dynamic_cast<Directory*>(resource)->findRecursive(name, flags);
                    if (result) {
                        break;
                    }
                }
            }
        }
        return result;
    }


    Resource* Directory::findRecursive(const std::string& name, const std::vector<OpFlags>& flags)const {
        Resource* result = nullptr;
        for (Resource* resource : m_contents) {
            if (resource->name() == name) {
                result = resource;
                break;
            }
            if (resource->type() == NodeType::DIR) {
                result = dynamic_cast<Directory*>(resource)->findRecursive(name, flags);
                if (result) {
                    break;
                }
            }
        }
        return result;
    }

}  // namespace sdds
