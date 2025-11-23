#include "file_storage.hpp"
#include "utils.hpp"
#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
#include <bitset>
#include <filesystem>
#include <iostream>

void FileStorage::create_file(std::string filepath, std::string byte_string) const {
    std::vector<uint8_t> bytes = string_to_bytes(byte_string);
    
    std::fstream file;
    file.open(filepath, std::ios::binary | std::ios::out);
    file.write(reinterpret_cast<char*>(bytes.data()), bytes.size() * sizeof(bytes[0]));
    file.close();
}
void FileStorage::delete_file(std::string filepath)  const{
    try
    {
        std::cout << filepath << std::endl;
        bool removed = std::filesystem::remove(filepath);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
void FileStorage::create_or_append(std::string filepath, std::string byte_string) const {
    std::vector<uint8_t> bytes = string_to_bytes(byte_string);
    std::fstream file;
    file.open(filepath, std::ios::binary | std::ios::app);
    file.write(reinterpret_cast<char*>(bytes.data()), bytes.size() * sizeof(bytes[0]));
    file.close();
}