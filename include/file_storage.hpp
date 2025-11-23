#ifndef FILESTORAGE_HPP
#define FILESTORAGE_HPP

#include <string>

class FileStorage {

public:
    void create_file(std::string filepath, std::string byte_string) const;
    void delete_file(std::string filepath) const;
    void create_or_append(std::string filepath, std::string byte_string) const;
};

#endif