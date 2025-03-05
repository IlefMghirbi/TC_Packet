#include "packet_extraction.h"

uint16_t extractAppProcessID(const std::vector<uint8_t>& buffer) {
    //check whether buffer size conforms to the parsing mechanism
    if (buffer.size() < 2) { 
        throw std::runtime_error("Buffer size error");
    }
    // According to the field sizes APID is 11bits long: divided into two bytes
    // big endian: get MSB from the first byte and combine with the LSB from the second byte
    // use a mask to only keep APID bits
    uint8_t MSB = buffer[0] & 0b00000111;
    uint8_t LSB = buffer[1];

    return (MSB << 8) | LSB;
}

uint16_t extractSeqCount(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 4) {
        std::cerr << "Buffer size error" << std::endl;
    }
    // sequence count is 14bits long: splitted between the 3rd and 4th bytes
    // big endian: get MSB from the 3rd byte, shift by 8bits, and combine 
    // with the LSB from the 4th byte
    // use a mask to only keep sequence count bits
    uint8_t MSB = buffer[2] & 0b00111111;
    uint8_t LSB = buffer[3];

    return (MSB << 8) | LSB;
}

uint16_t extractPacketLength(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 6) {
        std::cerr << "Buffer size error" << std::endl;
    }
    // packet length is 16bits long: splitted between the 5th and 6th bytes
    // big endian: get MSB from the 5th byte and combine with the LSB from the 6th byte
    uint8_t MSB = buffer[4];
    uint8_t LSB = buffer[5];

    return (MSB << 8) | LSB;
}

uint8_t extractServiceType(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 8) {
        std::cerr << "Buffer size error" << std::endl;
    }
    // service type is the 8th byte of the packet, 8bits long
    return buffer[7];
}

uint8_t extractServiceSubtype(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 9) {
        std::cerr << "Buffer size error" << std::endl;
    }
    // service subtype is the 8th byte of the packet, 8bits long
    return buffer[8];
}

std::vector<uint8_t> extractApplicationData(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < 10) {
        std::cerr << "Buffer size error in Application Data" << std::endl;
    }
    // given that sourceID is a byte long, Application data + spare bits start after the 10th
    // byte and end before Packet Error Control (2bytes long)
    return std::vector<uint8_t>(buffer.begin() + 10, buffer.end() - 2);
}
