#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

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

    uint16_t output = ((MSB << 8) | LSB) + 1;

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


int main() {

    //std::vector<uint8_t> buffer = {0b10110111, 0b01101001};
    Packet_ID packet_id{};
    Packet_Sequence_Control packet_seq_control{};
    Data_Field_Header data_field_header{};
    
    std::ifstream file("tc_packet.bin", std::ios::binary);

    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), {});
    std::cout << "Read " << buffer.size() << " bytes successfully" << std::endl;
    
    
    packet_id.application_process_ID = extractAppProcessID(buffer);
    std::cout << "Application Process ID : " << std::bitset<11>(packet_id.application_process_ID) << std::endl;
    
    packet_seq_control.seq_count = extractSeqCount(buffer);
    std::cout << "Sequence Count : " << packet_seq_control.seq_count << std::endl;

    uint16_t packet_length = extractPacketLength(buffer);
    std::cout << "Packet Length : "<< packet_length << std::endl;


    data_field_header.service_type = extractServiceType(buffer);
    data_field_header.service_subtype = extractServiceSubtype(buffer);

    std::cout << "Service type and service subtype: "<< std::bitset<8>(data_field_header.service_type) << std::endl;
    std::cout << "Service type and service subtype: "<< std::bitset<8>(data_field_header.service_subtype)<< std::endl;

    std::cout << "Application Data: 0x";
    for (size_t i = 10; i < buffer.size() ; ++i) {
        printf("%02X", buffer[i]);  
    }
    std::cout << std::endl;
    //for (size_t i = 10; i < buffer.size() ; ++i) {
    //    std::cout << std::bitset<8>(buffer[i]) << std::endl;  
    //}


    return 0;
}
