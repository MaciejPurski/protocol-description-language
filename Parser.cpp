#include <memory>
#include <bits/shared_ptr.h>
#include <climits>
#include <cstdarg>
#include "Parser.h"
#include "Sequence.h"
#include "RepeatOperation.h"

std::shared_ptr<Protocol> Parser::parse() {
	std::vector<std::shared_ptr<Packet>> packets;
	std::vector<std::shared_ptr<Sequence>> sequences;
	std::shared_ptr<Sequence> protocol;

	std::shared_ptr<Packet> p;
	std::shared_ptr<Sequence> s;

	/* Protocol might consist of packets and sequences,
	 * therefore we try to parse them until it is possible
	 */
	do {
		if ((p = parsePacket()) != nullptr)
			packets.push_back(p);

		if ((s = parseSequence()) != nullptr)
			sequences.push_back(s);

		if ((s = parseProtocol()) != nullptr)
			protocol = s;

	} while ((p != nullptr) || (s != nullptr));

	// TODO: nothing recognized

	return std::make_shared<Protocol>(packets, sequences, protocol);
}

std::shared_ptr<Sequence> Parser::parseSequence() {
	std::string name;
	std::vector<std::shared_ptr<Operation>> operations;

	// sequence must begin with a "sequence" keyword
	if (!consume(true, SEQUENCE_KEYWORD))
		return nullptr;

	if ((name = consumeIdentifier(false)).empty())
		return nullptr;

	if (!consume(false, OPEN_BRACK))
		return nullptr;

	std::shared_ptr<Block> block = parseBlock();

	if (block == nullptr)
		return nullptr;

	return std::make_shared<Sequence>(name, block);
}

std::shared_ptr<Block> Parser::parseBlock() {
	std::vector<std::shared_ptr<Operation>> operations;
	std::shared_ptr<Operation> o;

	while ((o = parseOperation()) != nullptr)
		operations.push_back(o);

	if (!consume(false, CLOSE_BRACK))
		return nullptr;


	return std::make_shared<Block>(operations);
}

std::shared_ptr<Sequence> Parser::parseProtocol() {
	std::string name;
	std::vector<std::shared_ptr<Operation>> operations;

	// sequence must begin with a "sequence" keyword
	if (!consume(true, PROTOCOL_KEYWORD))
		return nullptr;

	if ((name = consumeIdentifier(false)).empty())
		return nullptr;

	if (!consume(false, OPEN_BRACK))
		return nullptr;

	std::shared_ptr<Block> block = parseBlock();

	if (block == nullptr)
		return nullptr;

	return std::make_shared<Sequence>(name, block);
}

std::shared_ptr<Packet> Parser::parsePacket() {
    std::string name;
    std::vector<std::shared_ptr<Field>> fields;
    std::shared_ptr<Field> f;

    // packet must begin with a "packet" keyword
    if (!consume(true, PACKET_KEYWORD))
	    return nullptr;

	if ((name = consumeIdentifier(false)).empty())
		return nullptr;

	if (!consume(false, OPEN_BRACK))
		return nullptr;

	while ((f = parseField()) != nullptr)
		fields.push_back(f);

	if (!consume(false, CLOSE_BRACK))
		return nullptr;

    return std::make_shared<Packet>(name, fields);
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
std::shared_ptr<Reference> Parser::parseReference() {
	std::shared_ptr<Reference> ref;
	std::string name;

	if ((name = consumeIdentifier(true)).empty())
		return nullptr;

	ref = parseSequenceReference();

	if (ref == nullptr)
		ref = std::make_shared<PacketReference>();

	ref->name = name;

	if (!consume(false, SEMICOLON))
		return nullptr;

	return ref;
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

	if (!consume(true, ALT_KEYWORD))
		return nullptr;

	if (!consume(false, OPEN_BRACK))
		return nullptr;

	if ((b = parseBlock()) == nullptr)
		return nullptr;

	blocks.push_back(b);

	if (!consume(false, OR_KEYWORD))
		return nullptr;

	do  {
		if (!consume(false, OPEN_BRACK))
			return nullptr;

		if ((b = parseBlock()) == nullptr)
			return nullptr;

		blocks.push_back(b);
	} while (consume(true, OR_KEYWORD));

	return std::make_shared<AltOperation>(blocks);
}

std::shared_ptr<SequenceReference> Parser::parseSequenceReference() {
	if (!consume(true, OPEN_PARENT))
		return nullptr;

	if (!consume(false, CLOSE_PARENT))
		return nullptr;

	return std::make_shared<SequenceReference>();
}

std::shared_ptr<RepeatOperation> Parser::parseSimpleRepeatOperation() {
	unsigned int repeatFrom;
	unsigned int repeatTo;

	if (consume(true, ITERATE_KEYWORD)) {
		repeatFrom = 0;
		repeatTo = UINT_MAX;
	} else if (consume(true, DOITERATE_KEYWORD)) {
		repeatFrom = 1;
		repeatTo = UINT_MAX;
	} else if (consume(true, OPT_KEYWORD)) {
		repeatFrom = 0;
		repeatTo = 1;
	} else {
		return nullptr;
	}

	std::shared_ptr<Block> b;

	if (!consume(false, OPEN_BRACK))
		return nullptr;

	if ((b = parseBlock()) == nullptr)
		return nullptr;

	return std::make_shared<RepeatOperation>(repeatFrom, repeatTo, b);
}

std::shared_ptr<RepeatOperation> Parser::parseCompoundRepeatOperation() {
	unsigned int repeatFrom;
	unsigned int repeatTo;
	bool readFrom = false;
	bool commaSeperated = false;
	bool readTo = false;

	if (!consume(true, REPEAT_KEYWORD))
		return nullptr;

	if (!consume(false, OPEN_PARENT))
		return nullptr;

	if (consumeNumber(true, &repeatFrom)) {
		readFrom = true;
	} else {
	    repeatFrom = 0;
	}

	// if there is a comma, we might try to consume a second number
	if (consume(true, COMMA)) {
	    commaSeperated = true;

	    // if there is no second number after a comma
	    if (!consumeNumber(true, &repeatTo))
	    	repeatTo = UINT_MAX;
	} else if (!readFrom) {
		// () - case
		repeatTo = UINT_MAX;
	} else {
		// (3) - case
		repeatTo = repeatFrom;
	}

	if (!consume(false, CLOSE_PARENT))
		return nullptr;

    std::shared_ptr<Block> b;

    if (!consume(false, OPEN_BRACK))
    	return nullptr;

    if ((b = parseBlock()) == nullptr) {
        return nullptr;
    }

    return std::make_shared<RepeatOperation>(repeatFrom, repeatTo, b);
}

std::shared_ptr<Field> Parser::parseField() {
	std::shared_ptr<Type> type;
	std::string name;
	bool isAssigned = false;
	unsigned int valueAssigned;

	if ((type = parseType()) == nullptr)
		return nullptr;

	if ((name = consumeIdentifier(false)).empty())
		return nullptr;

	// there is a value assigned to the field
	if (consume(true, ASSIGNMENT)) {
		isAssigned = true;

		if (!consumeNumber(false, &valueAssigned))
			return nullptr;
	}

	if (!consume(false, SEMICOLON))
		return nullptr;

	return std::make_shared<Field>(type, name, isAssigned, valueAssigned);
}

std::shared_ptr<Type> Parser::parseType() {
	TokenType type;
	std::shared_ptr<Expression> length;

	if ()
		return nullptr;

	type = token.type;

	nextToken();

	if ((length = parseExpression()) == nullptr) {
		src.raiseError("Expected type length", token);
		return nullptr;
	}

	std::cout << "parse type\n";


	return std::make_shared<Type>(type, length);
}

std::shared_ptr<Expression> Parser::parseExpression() {
	unsigned int value;

	if (token.type != OPEN_PARENT)
		return nullptr;

	nextToken();

	if (token.type != DEC_NUMBER) {
		src.raiseError("Expected decimal number", token);
		return nullptr;
	}
	value = token.intValue;
	nextToken();

	if (token.type != CLOSE_PARENT) {
		src.raiseError("Expected closing parenthesis", token);
		return nullptr;
	}

	nextToken();

	return std::make_shared<Expression>(value);
}

bool Parser::consume(bool isPermissive, TokenType expected) {
	if (token.type == expected) {
		nextToken();

		return true;
	}

	// report an error
	if (!isPermissive) {
		src.raiseError("Expected " + Source::strToWhite("'" + Scanner::tokenToString(expected) + "'") + " before " +
		               Source::strToWhite("'" + Scanner::tokenToString(token.type) + "'"), token);

		nextToken();
	}

	return false;
}

std::string Parser::consumeIdentifier(bool isPermissive) {
	std::string str = "";

	if (token.type == IDENTIFIER) {
		str = token.stringValue;
		nextToken();
	} else if (!isPermissive) {
		src.raiseError("Expected identifier before " +
		               Source::strToWhite("'" + Scanner::tokenToString(token.type) + "'"), token);

		nextToken();
	}


	return str;
}

bool Parser::consumeNumber(bool isPermissive, unsigned int *number) {
	if (token.type == DEC_NUMBER || token.type == HEX_NUMBER) {
		*number = token.intValue;
		nextToken();

		return true;
	}

	if (!isPermissive) {
		src.raiseError("Expected identifier before " +
		               Source::strToWhite("'" + Scanner::tokenToString(token.type) + "'"), token);

		nextToken();
	}

	return false;
}

TokenType Parser::consumeType(bool isPermissive) {
	if (!consume(true, INT_TYPE) && !consume(true, UINT_TYPE) && !consume(true, BYTES_TYPE) &&
	    !consume(true, BITS_TYPE) && !consume(true, STRING_TYPE))
}