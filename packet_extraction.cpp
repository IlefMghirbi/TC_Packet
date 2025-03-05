#include "packet_extraction.h"

uint16_t extractAppProcessID(const std::vector<uint8_t>& buffer) {
    //check whether buffer size conforms to the parsing mechanism
    if (buffer.size() < 2) { 
        throw std::runtime_error("Buffer size error");
    }
    uint8_t MSB = buffer[0] & 0b00000111;
    uint8_t LSB = buffer[1];

    return (MSB << 8) | LSB;
}

uint16_t extractSeqCount(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 4) {
        throw std::runtime_error("Buffer size error");
    }
    uint8_t MSB = buffer[2] & 0b00111111;
    uint8_t LSB = buffer[3];

    return (MSB << 8) | LSB;
}

uint16_t extractPacketLength(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 6) {
        throw std::runtime_error("Buffer size error");
    }
    uint8_t MSB = buffer[4];
    uint8_t LSB = buffer[5];

    return (MSB << 8) | LSB;
}

uint8_t extractServiceType(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 8) {
        throw std::runtime_error("Buffer size error");
    }

    return buffer[7];
}

uint8_t extractServiceSubtype(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 9) {
        throw std::runtime_error("Buffer size error");
    }

    return buffer[8];
}

std::vector<uint8_t> extractApplicationData(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 10) {
        throw std::runtime_error("Buffer size error in Application Data");
    }
    return std::vector<uint8_t>(buffer.begin() + 10, buffer.end() - 2);
}
