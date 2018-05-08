#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_INTERPRETER_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_INTERPRETER_H


#include "Source.h"
#include "Scanner.h"
#include "Parser.h"
#include "Nodes/Sequence.h"
#include "Nodes/Packet.h"
#include "Nodes/Protocol.h"
#include "Analyzer/PacketsParser.h"

class Interpreter {
private:
	Source src;
	Scanner s;
	Parser p;
	PacketsParser packetsParser;
	bool assignedPid;
	unsigned int pidOffset;
	std::shared_ptr<Protocol> prot;
	std::unordered_map<std::string, std::shared_ptr<Packet>> packetsMap;
	std::unordered_map<uint64_t, std::shared_ptr<Packet>> pidMap;
	std::unordered_map<std::string, std::shared_ptr<Sequence>> sequenceMap;

	bool fillPacketsMap();
	bool fillSequenceMap();

public:
	Interpreter(const char *srcFile, const char *protocolFile) : src(srcFile, false), s(src), p(s, src), packetsParser(protocolFile) {
	}

	void start() {
		prot = p.parse();

		if (prot == nullptr)
			return;

		if (!fillPacketsMap())
			return;

		if (!fillSequenceMap())
			return;

		// TODO: different pids
		packetsParser.parsePackets(pidMap, 0, 1);
		packetsParser.showPacket();
	}

	bool findPacketPid(std::shared_ptr<Packet> p);

	bool checkPacketFields(std::shared_ptr<Packet> p);
};


#endif //PROTOCOL_DESCRIPTION_LANGUAGE_INTERPRETER_H
