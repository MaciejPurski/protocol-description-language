#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_INTERPRETER_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_INTERPRETER_H


#include "Source.h"
#include "Scanner.h"
#include "Parser.h"
#include "Nodes/Sequence.h"
#include "Nodes/Packet.h"
#include "Nodes/Protocol.h"
#include "Analyzer/PacketsParser.h"
#include <memory>

class Interpreter {
private:
	Source src;
	Scanner s;
	Parser p;
	std::shared_ptr<PacketsParser> packetsParser;
	bool assignedPid;
	bool interpretPackets;
	unsigned int pidOffset;
	unsigned int pidLength;
	std::unique_ptr<Protocol> prot;
	const char *fileName;

	bool fillPacketsMap();
	bool fillSequenceMap();

public:
	Interpreter(const char *srcFile, const char *protocolFile, bool ninterpretPackets) : src(srcFile, false), fileName(protocolFile), s(src), p(s, src),
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
		packetsParser->parsePackets();

		if (interpretPackets) {
			std::deque<std::string> callQueue;
			unsigned int position = 0;

			try {
				if (!prot->protocol->execute(callQueue, 0, position)) {
					std::cout << strToRed("Protocol not recognized") << std::endl;
				}
			} catch (std::exception &e) {
				std::cout << strToRed("Error: ") << e.what() << std::endl;
			}


			for (const auto &str : callQueue)
				std::cout << str << std::endl;

			if (position != packetsParser->getNPackets()) {
				std::cout << strToRed("Packets left unrecognized") << std::endl;
			}

		} else {
			packetsParser->showPacket();
		}

	}

	bool findPacketPid(std::unique_ptr<Packet> p);

	bool checkPacketFields(const std::unique_ptr<Packet> &p);
};


#endif //PROTOCOL_DESCRIPTION_LANGUAGE_INTERPRETER_H
