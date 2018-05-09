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
	bool interpretPackets;
	unsigned int pidOffset;
	std::shared_ptr<Protocol> prot;
	std::unordered_map<std::string, std::shared_ptr<Packet>> packetsMap;
	std::unordered_map<uint64_t, std::shared_ptr<Packet>> pidMap;


	bool fillPacketsMap();
	bool fillSequenceMap();

public:
	Interpreter(const char *srcFile, const char *protocolFile, bool ninterpretPackets) : src(srcFile, false), s(src), p(s, src), packetsParser(protocolFile),
	interpretPackets(ninterpretPackets) { }

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

		if (interpretPackets) {
			std::deque<std::string> callQueue;
			unsigned int position = 0;

			if (!prot->protocol->execute(callQueue, 0, position)) {
				std::cout << strToRed("Protocol not recognized") << std::endl;
			}


			for (const auto &str : callQueue)
				std::cout << str << std::endl;

			if (position != packetsParser.getNPackets()) {
				std::cout << strToRed("Packets left unrecognized") << std::endl;
			}

		} else {
			packetsParser.showPacket();
		}



	}

	bool findPacketPid(std::shared_ptr<Packet> p);

	bool checkPacketFields(std::shared_ptr<Packet> p);
};


#endif //PROTOCOL_DESCRIPTION_LANGUAGE_INTERPRETER_H
