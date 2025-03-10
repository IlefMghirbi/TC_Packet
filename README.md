# Telecommand Packet Parser

This project provides C++ scripts to parse and extract Telecommand (TC) packet information from a binary file.

## **1. Compilation & Execution**

### **1.1 Compile the Programs**
To compile the TC_Packet parser:
```sh
g++ TC_Packet.cpp packet_extraction.cpp -o TC_Packet
```
To compile the TC_Stream parser (in case of a stream of packets):
```sh
g++ TC_Stream.cpp packet_extraction.cpp -o TC_Stream
```

### **1.2 Run the Programs**

#### **Run the TC_Packet Parser**
This program reads a single Telecommand packet from a binary file (`tc_packet.bin` by default) and extracts key information.

```sh
./TC_Packet
```
**Expected output format:**
```
The parsed TC packet information: (Packet Total Length = 40):
  Application Process ID : 00111100011
  Sequence Count : 8
  Service Type: 11110001
  Service Subtype: 00011001
  Application Data: 0x3F80000040000000404000004080000040A0000040C0000040E00000

```

#### **Run the TC_Stream Parser**
If the binary file contains a stream of TC packets:

```sh
./TC_Stream
```
**Expected output format:**
```
Extracted 2 TC packets.
Packet 1 (Packet Total Length = 13):
  Application Process ID: 00110010100
  Sequence Count: 0
  Service Type: 11001000
  Service Subtype: 00000001
  Application Data: 0x00
Packet 2 (Packet Total Length = 13):
  Application Process ID: 00110010100
  Sequence Count: 1
  Service Type: 11001000
  Service Subtype: 00000011
  Application Data: 0x00

```

## **2. Troubleshooting**
- If `TC_Packet` or `TC_Stream` fail to run, ensure `tc_packet.bin` and  `tc_packet_stream.bin` exist in the same directory.


