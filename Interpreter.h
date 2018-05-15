#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_INTERPRETER_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_INTERPRETER_H


#include "Source.h"
#include "Scanner.h"
#include "Parser.h"
#include "Nodes/Sequence.h"
#include "Nodes/Packet.h"
#include "Nodes/Protocol.h"
#include "Analyzer/PacketsScanner.h"
#include "Analyzer/ProtocolParserState.h"
#include <memory>

class Interpreter {
private:
	Source src;
	Scanner s;
	Parser p;
	PacketsScanner packetsScanner;
	ProtocolParserState parserState;
	bool interpretPackets;
	std::unique_ptr<Protocol> prot;

	bool fillPacketsMap();
	bool fillSequenceMap();

public:
	Interpreter(const char *srcFile,
	            const char *protocolFile,
	            bool ninterpretPackets) : src(srcFile, false), packetsScanner(protocolFile),
	                                      parserState(packetsScanner),
	                                      s(src), p(s, src), interpretPackets(ninterpretPackets) { }

	void start() {
		prot = p.parse();

		if (prot == nullptr)
			return;

		if (!fillPacketsMap())
			return;

		if (!fillSequenceMap())
			return;

		if (interpretPackets) {
			std::deque<std::string> callQueue;
			unsigned int position = 0;

			if (!prot->protocol->execute(parserState, 0)) {
				std::cout << strToRed("Protocol not recognized") << std::endl;
			}

			parserState.showResult();

			if (!parserState.endOfBuffer()) {
				std::cout << strToRed("Packets left unrecognized") << std::endl;
			}

		} else {
			packetsScanner.showPacket();
		}

	}

	bool findPacketPid(std::unique_ptr<Packet> p);

	bool checkPacketFields(const std::unique_ptr<Packet> &p);
};


#endif //PROTOCOL_DESCRIPTION_LANGUAGE_INTERPRETER_H
