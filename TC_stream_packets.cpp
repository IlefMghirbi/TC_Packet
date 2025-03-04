#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "TC_Packet.h"


struct TCPacket {
    uint16_t packetLength; // Length of data field (excluding primary header)
    std::vector<uint8_t> data; // Full packet content
};

std::vector<TCPacket> parseTCPackets(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file\n";
        return {};
    }

    std::vector<TCPacket> packets;
    while (file) {
        std::vector<uint8_t> header(6); // Allocate vector for the 6-byte primary header
        if (!file.read(reinterpret_cast<char*>(header.data()), 6)) break;

        uint16_t packetLength = extractPacketLength(header);
        // Extract Packet Length (bytes 4 and 5, big-endian)
        //uint16_t packetLength = (header[4] << 8) | header[5];  // Convert to 16-bit integer

        // Compute total packet size (Primary Header + Data Field)
        size_t totalPacketSize = packetLength + 1 + 6;

        // Read the full packet
        TCPacket packet;
        packet.packetLength = packetLength;
        packet.data.resize(totalPacketSize);

        // Copy the header into the packet data vector
        std::copy(header.begin(), header.end(), packet.data.begin());

        // Read the remaining data field
        if (!file.read(reinterpret_cast<char*>(packet.data.data() + 6), packetLength + 1)) break;

        packets.push_back(packet);
    }

    return packets;
}

int main() {
    std::string filename = "tc_packet_stream.bin"; // Replace with your actual file name
    auto packets = parseTCPackets(filename);

    std::cout << "Extracted " << packets.size() << " TC packets.\n";
    for (size_t i = 0; i < packets.size(); ++i) {
        std::cout << "Packet " << i + 1 << " | Length: " << packets[i].packetLength + 1 + 6 << " bytes\n";
    }

    return 0;
}
