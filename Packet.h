#ifndef TKOM_PACKET_H
#define TKOM_PACKET_H

#include "PacketTemplate.h"

class Packet {
private:
	unsigned char *buffer;
	PacketTemplate *packetTemplate;
public:
	Packet () {

	}

	~Packet() {
		delete buffer;
	}

	std::ostream &operator<<(std::ostream &o) {
		for (Field f : packetTemplate->fields) {
			o << f.toString(buffer);
		}

		o << std::endl;
	}

};


#endif //TKOM_PACKET_H
