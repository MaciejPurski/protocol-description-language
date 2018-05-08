#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_PACKETSPARSER_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_PACKETSPARSER_H


#include <fstream>
#include <unordered_map>
#include "AnalyzerPacket.h"

class PacketsParser {
private:
	std::vector<AnalyzerPacket> packets;
	std::fstream file;

	uint64_t parseUInt(char *buf, unsigned int size);

	int64_t parseInt(char *buf, unsigned int size);

	std::string parseString(char *buf, unsigned int size);

	void getBytes(std::vector<char> &buf, unsigned int n);


public:
	PacketsParser(const char *fname);

	void parsePackets(std::unordered_map<uint64_t, std::shared_ptr<Packet>> &pidMap,
	                  unsigned int pidOffset, unsigned int pidLenth);

	void showPacket();

	unsigned int evaluateFieldLength(std::vector<AnalyzerField> &fields, std::shared_ptr<Field> f);

	const AnalyzerPacket &getPacket(unsigned int index) {
		if (index < packets.size())
			return packets[index];
		else
			throw std::runtime_error("Index out of bounds of packets array");
	}

	unsigned long getNPackets() {
		return packets.size();
	}
};


#endif //PROTOCOL_DESCRIPTION_LANGUAGE_PACKETSPARSER_H
