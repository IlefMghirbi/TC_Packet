#ifndef PACKET_EXTRACTION_H
#define PACKET_EXTRACTION_H

#include <vector>
#include <cstdint>
#include <stdexcept>


/// @brief structure to store the needed information
struct Packet_Information {
    uint16_t    application_process_ID;
    uint16_t    seq_count;
    uint16_t    length;
    uint8_t     service_type;
    uint8_t     service_subtype;
    std::vector<uint8_t> application_data;
};

/// @brief structure to store packet information + one packet content
struct TC_Packet {
    Packet_Information packet_information;
    std::vector<uint8_t> data; 
};

/// @brief function to extract the Application Process ID(APID) field of a TC packet
/// @param buffer: raw packet format
/// @return APID
uint16_t extractAppProcessID(const std::vector<uint8_t>& buffer);

/// @brief function to extract the sequence count field of a TC packet
/// @param buffer: raw packet format
/// @return  sequence count
uint16_t extractSeqCount(const std::vector<uint8_t>& buffer);

/// @brief function to extract the packet length
/// @param buffer: raw packet format
/// @return packet length
uint16_t extractPacketLength(const std::vector<uint8_t>& buffer);

/// @brief function to extract service type field of a TC packet
/// @param buffer: raw packet format
/// @return service type
uint8_t extractServiceType(const std::vector<uint8_t>& buffer);

/// @brief function to extract service subtype field of a TC packet
/// @param buffer: raw packet format
/// @return service subtype
uint8_t extractServiceSubtype(const std::vector<uint8_t>& buffer);

/// @brief function to extract the application data of a TC packet (including spare bits)
/// @param buffer: raw packet format
/// @return application data (including spare bits)
std::vector<uint8_t> extractApplicationData(const std::vector<uint8_t>& buffer);

#endif // PACKET_EXTRACTION_H
