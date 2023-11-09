// In Tae Chung | 128 958 220
// itchung@myseneca.ca
// Nov 8, 2023
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <fstream>
//#include <stdexcept>
#include "Filesystem.h"
#include "File.h"

namespace sdds {
    Filesystem::Filesystem(const std::string filename, const std::string root) {
        // open file for reading
        std::ifstream file(filename);
        if (file.fail()) {
            throw std::invalid_argument("File failed to open.");
        }

        // create root directory with 'root'
        m_root = new Directory(root);
        // set current directory to root
        m_current = m_root;

        // reading each line from file
        std::string line;
        while (std::getline(file, line)) {
            Directory* curDir = m_root;
            // check for file
            if (line.find('|') != std::string::npos) {
                // File
                std::vector<std::string> lineTokens = split(line, '|');
                std::vector<std::string> pathTokens = split(lineTokens.front(), '/');

                // move down paths, create directories as needed
                for (size_t i = 0; i < pathTokens.size() - 1; i++) {
                    Resource* foundResource = curDir->find(pathTokens[i] + '/');
                    if (foundResource == nullptr) {
                        Directory* newDir = new Directory(pathTokens[i] + '/');
                        *curDir += newDir;
                        curDir = newDir;
                    } else {
                        curDir = static_cast<Directory*>(foundResource);
                    }
                }
                // create and add file if it does not exist
                if (curDir->find(pathTokens.back()) == nullptr) {
                    File* newFile = new File(pathTokens.back(), lineTokens.back());
                    *curDir += newFile;
                }
            } else {
                // Directory
                std::vector<std::string> pathTokens = split(line, '/');
                // move down paths, creating directories as needed
                for (size_t i = 0; i < pathTokens.size(); i++) {
                    Resource* foundResource = curDir->find(pathTokens[i] + '/');
                    if (foundResource == nullptr) {
                        Directory* newDir = new Directory(pathTokens[i] + '/');
                        *curDir += newDir;
                        curDir = newDir;
                    } else {
                        curDir = static_cast<Directory*>(foundResource);
                    }
                }
            }
        }
    }

    Filesystem::~Filesystem() {
        delete m_root;
    }

    Filesystem& Filesystem::operator+=(Resource* resource) {
        *m_current += resource;
        return *this;
    }

    Directory* Filesystem::change_directory(const std::string& dirName) {
        if (dirName.empty()) {
            m_current = m_root;
        } else {
            Resource* newRes = m_current->find(dirName);
            if (newRes == nullptr || newRes->type() == NodeType::FILE) {
                throw std::invalid_argument("Cannot change directory! " + dirName + " not found!");
            } else {
                m_current = static_cast<Directory*>(newRes);
            }
        }
        return m_current;
    }

    Directory* Filesystem::get_current_directory() const {
        return m_current;
    }

    std::vector<std::string> Filesystem::split(std::string str, const char delim) {
        std::vector<std::string> tokens;
        size_t pos = 0;
        while ((pos = str.find(delim)) != std::string::npos) {
            tokens.push_back(this->trimSpaces(str.substr(0, pos)));
            str.erase(0, pos + 1);
        }
        str = this->trimSpaces(str);
        if (!str.empty()) {
            tokens.push_back(str);
        }
        return tokens;
    }

    std::string Filesystem::trimSpaces(std::string str) {
        str.erase(0, str.find_first_not_of(' '));
        str.erase(str.find_last_not_of(' ') + 1);
        return str;
    }

    // move methods:
    Filesystem::Filesystem(Filesystem&& other) {
        m_root = std::move(other.m_root);
        m_current = std::move(other.m_current);

        other.m_root = nullptr;
        other.m_current = nullptr;
    }
    Filesystem& Filesystem::operator=(Filesystem&& other) {
        if (this != &other) {
            delete m_root;

            m_root = std::move(other.m_root);
            m_current = std::move(other.m_current);

            other.m_root = nullptr;
            other.m_current = nullptr;
        }
        return *this;
    }

}  // namespace sdds
