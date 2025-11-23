#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <cstdint>

std::vector<uint8_t> string_to_bytes(std::string byte_string);

std::string generate_file_name();

std::string random_identifier();
#endif