#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "TC_Packet.h"

struct TC_Packet {
    Packet_Information packet_information;
    std::vector<uint8_t> data; // Full packet content
};

std::vector<TC_Packet> extractAllPackets(const std::string &filename){
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file!\n";
        return {};
    }

    std::vector<TC_Packet> packets;
    while(file){
        std::vector<uint8_t> header(6); // Allocate vector for the 6-byte primary header
        if (!file.read(reinterpret_cast<char*>(header.data()), 6)) break;

        // Extract Packet Length (bytes 4 and 5, big-endian)
        uint16_t packetLength = (header[4] << 8) | header[5];  // Convert to 16-bit integer

        // Compute total packet size (Primary Header + Data Field)
        size_t totalPacketSize = packetLength + 1 + 6;

        // Read the full packet
        TC_Packet packet;
        packet.packet_information.length = packetLength;
        packet.data.resize(totalPacketSize);

        // Copy the header into the packet data vector
        std::copy(header.begin(), header.end(), packet.data.begin());

        // Read the remaining data field
        if (!file.read(reinterpret_cast<char*>(packet.data.data() + 6), packetLength + 1)) break;

        packets.push_back(packet);
    }
}

int main() {


    std::string filename = "tc_packet_stream.bin"; 
    auto packets = extractAllPackets(filename);
    std::cout << "Extracted " << packets.size() << " TC packets.\n";
    for (size_t i = 0; i < packets.size(); ++i) {
        std::cout << "Packet " << i + 1 << " | Length: " << packets[i].packet_information.length + 1 + 6 << " bytes\n";
    }
    //std::ifstream file("tc_packet_stream.bin", std::ios::binary);
    //if (!file) {
    //    std::cerr << "Error opening file!\n";
    //    return 1;
    //}
//
    //const size_t headerSize = 10; 
    //std::vector<uint8_t> headerBuffer(headerSize);
    //std::vector<uint8_t> dataBuffer{};
    //headerBuffer.reserve(10);
    //std::vector<Packet_Information> stream_packets {};
    //stream_packets.reserve(10);
    //int packet_count {};
//
    //while (file.read(reinterpret_cast<char*>(headerBuffer.data()), headerSize)){
//
    //    //std::cout << "Read " << headerBuffer.size() << " bytes successfully" << std::endl;
    //    stream_packets[packet_count].application_process_ID = extractAppProcessID(headerBuffer);
    //    stream_packets[packet_count].seq_count = extractSeqCount(headerBuffer);
    //    stream_packets[packet_count].service_type = extractServiceType(headerBuffer);
    //    stream_packets[packet_count].service_subtype = extractServiceSubtype(headerBuffer);
    //    stream_packets[packet_count].length = extractPacketLength(headerBuffer);
//
    //    std::cout << "Application Process ID : " << 
    //    std::bitset<11>(stream_packets[packet_count].application_process_ID) << std::endl;
    //    std::cout << "Sequence Count : " << stream_packets[packet_count].seq_count << std::endl;
    //    std::cout << "Service type and service subtype: "<< std::bitset<8>(stream_packets[packet_count].service_type) << std::endl;
    //    std::cout << "Service type and service subtype: "<< std::bitset<8>(stream_packets[packet_count].service_subtype)<< std::endl;
    //    
    //    dataBuffer.reserve(stream_packets[packet_count].length);
    //    std::cout << "data length: "<< stream_packets[packet_count].length << std::endl;

        //if (!file.read(reinterpret_cast<char*>(dataBuffer.data()), stream_packets[packet_count].length)) {
        //    std::cerr << "Error: Could not read full data section!\n";
        //    break;
        //}
//
        //// Print first 4 bytes of data as hex (if available)
        //std::cout << "First 4 bytes of data: ";
        //for (size_t i = 0; i < std::min((size_t)4, dataBuffer.size()); ++i) {
        //    printf("%02X ", dataBuffer[i]);
        //}
        //std::cout << "\n";
    //}



    return 0;
}
