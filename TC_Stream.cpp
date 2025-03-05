#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "packet_extraction.h"


std::vector<TC_Packet> extractAllPackets(const std::string &filename){
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Could not open file and Exited"<<std::endl;
        return {};
    }

    std::vector<TC_Packet> packets;
    std::vector<Packet_Information> packet_information; //information about all stream packets
    while(file){
        std::vector<uint8_t> header(6);
        if (!file.read(reinterpret_cast<char*>(header.data()), 6)){
            std::cout << "Could not parse header" << std::endl;
            break;
        } 

        uint16_t packetLength = extractPacketLength(header);
        size_t totalPacketSize = packetLength + 1 + 6;

        TC_Packet packet;
        packet.packet_information.length = extractPacketLength(header);
        packet.data.resize(totalPacketSize);

        // Copy the header into the packet data vector
        std::vector<uint8_t> packetData(totalPacketSize);
        std::copy(header.begin(), header.end(), packet.data.begin());

        // Read the remaining data field
        if (!file.read(reinterpret_cast<char*>(packet.data.data() + 6), packetLength + 1)){
            std::cout << "Could not parse data" << std::endl;
            break;
        }

        packet.packet_information.application_process_ID = extractAppProcessID(packet.data);
        packet.packet_information.seq_count = extractSeqCount(packet.data);
        packet.packet_information.service_type = extractServiceType(packet.data);
        packet.packet_information.service_subtype = extractServiceSubtype(packet.data);
        packet.packet_information.application_data = extractApplicationData(packet.data);
        packets.push_back(packet);
    }

    return packets;
}

int main() {


    std::string filename = "tc_packet_stream.bin"; 
    auto packets = extractAllPackets(filename);
    std::cout << "Extracted " << packets.size() << " TC packets.\n";
    for (size_t i = 0; i < packets.size(); ++i) {
        std::cout << "Packet " << i + 1 << std::endl;
        std::cout << "  Application Process ID: " << std::bitset<11>(packets[i].packet_information.application_process_ID)<< std::endl;
        std::cout << "  Sequence Count: " << packets[i].packet_information.seq_count << std::endl;
        std::cout << "  Service Type: " << static_cast<int>(packets[i].packet_information.service_type) << std::endl;
        std::cout << "  Service Subtype: " << static_cast<int>(packets[i].packet_information.service_subtype) << std::endl;
        std::cout << "  Application Data: 0x";
        for (uint8_t byte : packets[i].packet_information.application_data) {
            printf("%02X", byte);
        }
        std::cout << std::endl;
    }


    
    return 0;
}
