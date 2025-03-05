to compile and run the packet extraction code, navigate to the tc_parsing directory and run:
g++ TC_Packet.cpp packet_extraction.cpp -o TC_Packet
then execute:
./TC_Packet
the output will show something similar to:
the parsed tc packet information: (packet total length = 40): 01011110011
sequence count: 2
service type: 1111001
service sub type: 1111001
application data: 0xFA388800808000

to compile and run the stream parsing code, run:
g++ TC_Stream.cpp TC_parsing.cpp -o TC_Stream
then execute:
./TC_Stream
the output will show something like:
extracted 2 tc packets
packet 1 (packet total length = 13):
sequence count: 0
service type: 1101000
service sub type: 1010100
application data: 0x00

packet 2 (packet total length = 13):
sequence count: 1
service type: 1101000
service sub type: 1010100
application data: 0x00
