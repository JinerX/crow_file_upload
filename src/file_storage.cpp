#include "file_storage.hpp"
#include "utils.hpp"
#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
#include <bitset>
#include <filesystem>
#include <iostream>
#include <expected>

std::expected<void, std::string>  FileStorage::create_file(std::string filepath, std::string byte_string) const {
    std::vector<uint8_t> bytes = string_to_bytes(byte_string);
    

    std::ofstream file(filepath, std::ios::binary);
    if (!file) return std::unexpected("Failed to open file");
    file.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    if (!file) return std::unexpected("Write failed");
    file.close();

    return {};
}

std::expected<void, std::string> FileStorage::delete_file(std::string filepath) const {
    try {
        std::cout << filepath << std::endl;
        bool removed = std::filesystem::remove(filepath);
        if (!removed) {
            return std::unexpected("Failed to delete file");
        }
    } catch (const std::exception& e) {
        return std::unexpected(e.what());
    }

    return {};
}

std::expected<void, std::string> FileStorage::create_or_append(std::string filepath, std::string byte_string) const {
    std::vector<uint8_t> bytes = string_to_bytes(byte_string);
    std::fstream file;
    file.open(filepath, std::ios::binary | std::ios::app);
    if (!file.is_open()) return std::unexpected("Failed to open file");
    file.write(reinterpret_cast<char*>(bytes.data()), bytes.size() * sizeof(bytes[0]));
    if (!file.good()) return std::unexpected("Write failed");
    file.close();
    return {};
}