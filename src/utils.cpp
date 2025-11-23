#include "utils.hpp"
#include <string>
#include <vector>
#include <bitset>
#include <cstdint>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <random>

std::string random_identifier() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<uint64_t> distribution(0, 0xFFFFFFFFFFFFFFFF);

    auto gen_random = [&](){return distribution(gen);};

    uint64_t block1 = gen_random();
    uint64_t block2 = gen_random();
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(16) << block1 << std::hex << std::setfill('0') << std::setw(16) << block2;
    return oss.str();
}


std::vector<uint8_t> string_to_bytes(std::string byte_string) {
    std::vector<uint8_t> bytes;
    for (int i=0; i < byte_string.size(); i+=8) {
        std::string curr = byte_string.substr(i,8);
        if (curr.size() < 8) {
            curr.append(8 - curr.size(), '0');
        }
        std::bitset<8> bits(curr);
        bytes.push_back(static_cast<uint8_t>(bits.to_ulong()));
    }
    return bytes;
}

std::string generate_file_name() {
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    std::tm time_data {};
    #ifdef _WIN32
        localtime_s(&time_data, &t);
    #else
        localtime_r(&t, &time_data);
    #endif
    oss << std::put_time(&time_data, "%Y_%m_%d_%H_%M_%S");

    std::string timestamp = oss.str();
    std::string random_value = random_identifier();
    return timestamp + "_" + random_value + ".bin";
}
