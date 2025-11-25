#ifndef FILESTORAGE_HPP
#define FILESTORAGE_HPP

#include <string>
#include <expected>

class FileStorage {

public:
    std::expected<void, std::string>  create_file(std::string filepath, std::string byte_string) const;
    std::expected<void, std::string>  delete_file(std::string filepath) const;
    std::expected<void, std::string>  create_or_append(std::string filepath, std::string byte_string) const;
};

#endif