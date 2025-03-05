#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>

struct Packet_ID{
    uint8_t version_number: 3;
    uint8_t type: 1;
    uint8_t DFH_flag: 1;
    uint16_t application_process_ID: 11;
};

struct Packet_Sequence_Control{
    uint16_t seq_count: 14;
};

struct Packet_Length{
    uint16_t length;
};

struct Data_Field_Header{
    uint8_t service_type;
    uint8_t service_subtype;

};

struct Packet_Information {
    uint16_t    application_process_ID: 11;
    uint16_t    seq_count: 14;
    uint16_t    length;
    uint8_t     service_type;
    uint8_t     service_subtype;
    std::vector<uint8_t> application_data;
};

struct TC_Packet {
    Packet_Information packet_information;
    std::vector<uint8_t> data; 
};

uint16_t extractAppProcessID (const std::vector<uint8_t> buffer){
    
    if (buffer.size() < 2) {
        throw std::runtime_error("Buffer size error");
    }
    uint8_t MSB = buffer[0]& 0b00000111;
    uint8_t LSB = buffer[1];

    uint16_t output = (MSB << 8) | LSB;

    return output;
} 

uint16_t extractSeqCount (const std::vector<uint8_t> buffer){
    if (buffer.size() < 4) {
        throw std::runtime_error("Buffer size error");
    }
    uint8_t MSB = buffer[2]& 0b00111111;
    uint8_t LSB = buffer[3];

    uint16_t output = (MSB << 8) | LSB;

    return output;
}

uint16_t extractPacketLength (const std::vector<uint8_t> buffer){
    if (buffer.size() < 6) {
        throw std::runtime_error("Buffer size error");
    }
    uint8_t MSB = buffer[4];
    uint8_t LSB = buffer[5];

    uint16_t output = ((MSB << 8) | LSB);

    return output;
}

uint8_t extractServiceType (const std::vector<uint8_t> buffer){
    if (buffer.size() < 8) {
        throw std::runtime_error("Buffer size error");
    }

    uint8_t output = buffer[7];

    return output;
}

uint8_t extractServiceSubtype (const std::vector<uint8_t> buffer){
    if (buffer.size() < 9) {
        throw std::runtime_error("Buffer size error");
    }

    uint8_t output = buffer[8];

    return output;
}
