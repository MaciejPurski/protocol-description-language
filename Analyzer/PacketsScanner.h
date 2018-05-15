#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_PACKETSPARSER_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_PACKETSPARSER_H

#include "AnalyzerPacket.h"
#include "../Nodes/Packet.h"
#include <unordered_map>
#include <fstream>

class PacketsScanner {
private:
	unsigned int currentPosition = 0;

	uint64_t parseUInt(char *buf, unsigned int size);

	int64_t parseInt(char *buf, unsigned int size);

	std::string parseString(char *buf, unsigned int size);

	void getBytes(std::vector<char> &buf, unsigned int n);

	std::vector<AnalyzerPacket> packets;
	std::fstream file;
public:
	PacketsScanner(const char *fileName);

	void parsePackets(std::unordered_map<uint64_t, std::unique_ptr<Packet>> pidMap,
	                   unsigned int pidOffset, unsigned int pidLength);

	void showPacket();

	unsigned int evaluateFieldLength(std::vector<AnalyzerField> &fields, std::unique_ptr<Field> &f);

	const AnalyzerPacket &getPacket() {
		if (currentPosition < packets.size())
			return packets[currentPosition];
		else
			throw std::runtime_error("Index out of bounds of packets array");
	}

	const AnalyzerPacket &getPacket(unsigned int index) {
		if (index < packets.size())
			return packets[index];
		else
			throw std::runtime_error("Index out of bounds of packets array");
	}


	unsigned long getNPackets() {
		return packets.size();
	}



	unsigned int getCurrentPosition() {
		return currentPosition;
	}

	void incrementCurrentPosition() {
		currentPosition++;
	}

	void setCurrentPosition(unsigned int newPos) {
		currentPosition = newPos;
	}
};


#endif
