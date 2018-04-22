#include <memory>
#include <bits/shared_ptr.h>
#include <climits>
#include "Parser.h"
#include "Sequence.h"
#include "RepeatOperation.h"

std::shared_ptr<Protocol> Parser::parse() {
	std::vector<std::shared_ptr<Packet>> packets;
	std::vector<std::shared_ptr<Sequence>> sequences;
	std::shared_ptr<Sequence> protocol;

	std::shared_ptr<Packet> p;
	std::shared_ptr<Sequence> s;

	nextToken();

	/* Protocol might consist of packets and sequences,
	 * therefore we try to parse them until it is possible
	 */
	do {
		p = parsePacket();
		if (p != nullptr)
			packets.push_back(p);

		s = parseSequence();
		if (s != nullptr)
			sequences.push_back(s);

	} while (p != nullptr || s != nullptr);

	/*
	 * At the end there should be "protocol" definition
	 */
	if ((protocol = parseProtocol()) == nullptr) {
		src.raiseError("Expected protocol definition at the end of file", token);

		return nullptr;
	}

	return std::make_shared<Protocol>(packets, sequences, protocol);
}

std::shared_ptr<Sequence> Parser::parseSequence() {
	std::string name;
	std::vector<std::shared_ptr<Operation>> operations;

	// sequence must begin with a "sequence" keyword
	if (token.type != SEQUENCE_KEYWORD)
		return nullptr;

	nextToken();
	if (token.type != IDENTIFIER) {
		src.raiseError("Expected sequence name identifier", token);

		return nullptr;
	}

	name = token.stringValue;

	nextToken();
	std::shared_ptr<Block> block = parseBlock();

	if (block == nullptr) {
		src.raiseError("Expected block definition", token);
		return nullptr;
	}

	return std::make_shared<Sequence>(name, block);
}

std::shared_ptr<Block> Parser::parseBlock() {
	std::vector<std::shared_ptr<Operation>> operations;
	std::shared_ptr<Operation> o;

	if (token.type != OPEN_BRACK) {
		return nullptr;
	}

	nextToken();

	while ((o = parseOperation()) != nullptr)
		operations.push_back(o);

	if (token.type != CLOSE_BRACK) {
		src.raiseError("Expected closing bracket", token);
		return nullptr;
	}
	nextToken();

	return std::make_shared<Block>(operations);
}

std::shared_ptr<Sequence> Parser::parseProtocol() {
	std::string name;
	std::vector<std::shared_ptr<Operation>> operations;

	// sequence must begin with a "sequence" keyword
	if (token.type != PROTOCOL_KEYWORD)
		return nullptr;

	nextToken();
	if (token.type != IDENTIFIER) {
		src.raiseError("Expected protocol name identifier", token);

		return nullptr;
	}

	name = token.stringValue;

	nextToken();
	std::shared_ptr<Block> block = parseBlock();

	if (block == nullptr) {
		src.raiseError("Expected block definition", token);
		return nullptr;
	}

	return std::make_shared<Sequence>(name, block);
}

std::shared_ptr<Packet> Parser::parsePacket() {
	return nullptr;
}

std::shared_ptr<Operation> Parser::parseOperation() {
	std::shared_ptr<Operation> op;

	if ((op = parseReference()) != nullptr)
		return op;

	if ((op = parseRepeatOperation()) != nullptr)
		return op;

	if ((op = parseAltOperation()) != nullptr)
		return op;

	return nullptr;
}

/*
 * A reference might be either a reference to a packet
 * or a sequence
 */
std::shared_ptr<Operation> Parser::parseReference() {
	std::shared_ptr<Operation> ref;
	std::string name;

	if (token.type != IDENTIFIER)
		return nullptr;

	name = token.stringValue;
	nextToken();

	if ((ref = parsePacketReference()) != nullptr) {
		auto p = std::static_pointer_cast<PacketReference>(ref);

		p->name = name;
		return p;
	}

	if ((ref = parseSequenceReference()) != nullptr) {
		auto s = std::static_pointer_cast<SequenceReference>(ref);

		s->name = name;
		return s;
	}

	src.raiseError("Expected \'(\' token or \';\' to parse a reference", token);

	return nullptr;
}


std::shared_ptr<RepeatOperation> Parser::parseRepeatOperation() {
	std::shared_ptr<RepeatOperation> op;

	if ((op = parseSimpleRepeatOperation()) != nullptr)
		return op;

	if ((op = parseCompoundRepeatOperation()) != nullptr)
		return op;

	return nullptr;
}

std::shared_ptr<AltOperation> Parser::parseAltOperation() {
	std::vector<std::shared_ptr<Block>> blocks;
	std::shared_ptr<Block> b;

	if (token.type != ALT_KEYWORD)
		return nullptr;
	nextToken();

	b = parseBlock();
	if (b == nullptr) {
		src.raiseError("Expected block after \'alt\' keyword", token);
		return nullptr;
	}
	blocks.push_back(b);

	if (token.type != OR_KEYWORD) {
		src.raiseError("Expected at least one 'or' statement after 'alt' block", token);
		return nullptr;
	}

	do  {
		nextToken();
		b = parseBlock();
		if (b == nullptr) {
			src.raiseError("Expected block after \'or\' keyword", token);
			return nullptr;
		}

		blocks.push_back(b);

	} while (token.type == OR_KEYWORD);

	return std::make_shared<AltOperation>(blocks);
}

std::shared_ptr<PacketReference> Parser::parsePacketReference() {
	if (token.type != SEMICOLON)
		return nullptr;

	nextToken();

	return std::make_shared<PacketReference>();
}

std::shared_ptr<SequenceReference> Parser::parseSequenceReference() {
	if (token.type != OPEN_PARENT)
		return nullptr;

	nextToken();

	if (token.type != CLOSE_PARENT)
		return nullptr;

	nextToken();

	if (token.type != SEMICOLON)
		return nullptr;

	nextToken();

	return std::make_shared<SequenceReference>();
}

std::shared_ptr<RepeatOperation> Parser::parseSimpleRepeatOperation() {
	unsigned int repeatFrom;
	unsigned int repeatTo;

	if (token.type == ITERATE_KEYWORD) {
		repeatFrom = 0;
		repeatTo = UINT_MAX;

		nextToken();
	} else if (token.type == DOITERATE_KEYWORD) {
		repeatFrom = 1;
		repeatTo = UINT_MAX;

		nextToken();
	} else if (token.type == OPT_KEYWORD) {
		repeatFrom = 0;
		repeatTo = 1;

		nextToken();
	} else {
		return nullptr;
	}

	std::shared_ptr<Block> b;

	if ((b = parseBlock()) == nullptr) {
		src.raiseError("Expected block after \'" + token.stringValue + "\'" + " keyword", token);
		return nullptr;
	}


	return std::make_shared<RepeatOperation>(repeatFrom, repeatTo, b);
}

std::shared_ptr<RepeatOperation> Parser::parseCompoundRepeatOperation() {
	return std::shared_ptr<RepeatOperation>();
}
