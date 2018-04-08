#ifndef TKOM_PACKETLEXER_H
#define TKOM_PACKETLEXER_H


#include <map>
#include "PacketTemplate.h"
#include "Packet.h"

class PacketLexer {
private:
	using PacketsContainer = std::multimap<int, PacketTemplate*>;
	PacketsContainer packetTemplates;

public:
	PacketLexer() {}

	~PacketLexer() {
		/*for (std::pair<int, PacketTemplate*> &x : packetTemplates)
			delete x.second;*/
	}

	void addPacketTemplate(PacketTemplate *pT) {
		packetTemplates.insert(pT);
	}

	Packet nextPacket(std::istream &s);
};


#endif //TKOM_PACKETLEXER_H
