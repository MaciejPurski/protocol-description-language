#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H


#include "Scanner.h"
#include "Protocol.h"
#include "Sequence.h"
#include "RepeatOperation.h"
#include "AltOperation.h"
#include "PacketReference.h"
#include "SequenceReference.h"

class Parser {
private:
	Scanner &s;
	Source &src;
	Token token;

	void nextToken() {
		token = s.nextToken();
	}

public:
	Parser(Scanner &ns, Source &nsrc) : s(ns), src(nsrc) {}

	std::shared_ptr<Protocol>  parse();

	std::shared_ptr<Packet> parsePacket();

	std::shared_ptr<Sequence> parseSequence();

	std::shared_ptr<Sequence> parseProtocol();

	std::shared_ptr<Block> parseBlock();

	std::shared_ptr<Operation> parseOperation();

	std::shared_ptr<Operation> parseReference();

	std::shared_ptr<RepeatOperation> parseRepeatOperation();

	std::shared_ptr<AltOperation> parseAltOperation();

	std::shared_ptr<PacketReference> parsePacketReference();

	std::shared_ptr<SequenceReference> parseSequenceReference();

	std::shared_ptr<RepeatOperation> parseSimpleRepeatOperation();

	std::shared_ptr<RepeatOperation> parseCompoundRepeatOperation();
};


#endif //TKOM_PARSER_H
