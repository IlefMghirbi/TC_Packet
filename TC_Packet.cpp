#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>
#include "packet_extraction.h"


int main() {

    // open the binary file
    std::ifstream file("tc_packet.bin", std::ios::binary);
    if (!file) {
        std::cerr << "Could not open file and Exited" << std::endl;
        return -1;
    }

    Packet_Information packet_information {};
    // read the packet and write the raw data into the buffer
    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), {});
    
    // get the packet information
    packet_information.application_process_ID = extractAppProcessID(buffer);
    packet_information.seq_count = extractSeqCount(buffer);
    packet_information.length = extractPacketLength(buffer) + 1;
    packet_information.service_type = extractServiceType(buffer);
    packet_information.service_subtype = extractServiceSubtype(buffer);
    packet_information.application_data = extractApplicationData(buffer);

    // log the extracted information of the TC packet
    std::cout << "The parsed TC packet information: "<< std::endl;
    std::cout << "  Application Process ID : " << std::bitset<11>(packet_information.application_process_ID) << std::endl;
    std::cout << "  Sequence Count : " << packet_information.seq_count << std::endl;
    std::cout << "  Packet Length : "<< packet_information.length << std::endl;
    std::cout << "  Service type and service subtype: "<< std::bitset<8>(packet_information.service_type) << std::endl;
    std::cout << "  Service type and service subtype: "<< std::bitset<8>(packet_information.service_subtype)<< std::endl;
    std::cout << "  Application Data: 0x";
    for (uint8_t byte : packet_information.application_data) {
        printf("%02X", byte);
    }
    std::cout << std::endl;



    return 0;
}
