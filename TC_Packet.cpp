#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>
#include "TC_Packet.h"


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

    uint16_t packet_length = extractPacketLength(buffer) + 1;
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
