#include <memory>
#include <climits>
#include <cstdarg>
#include "Parser.h"
#include "Colors.h"
#include "Nodes/PacketReference.h"

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

	} while ((p != nullptr) || (s != nullptr));

	if (src.getNErrors() > 0) {
		std::cout << "parsing failed\n";
		return nullptr;
	}

	if ((protocol = parseProtocol()) == nullptr) {
		return nullptr;
	}

	return std::make_shared<Protocol>(packets, sequences, protocol);
}

std::shared_ptr<Sequence> Parser::parseSequence() {
	std::string name;
	std::vector<std::shared_ptr<Operation>> operations;

	// sequence must begin with a "sequence" keyword
	if (!consume(true, SEQUENCE_KEYWORD))
		return nullptr;

	if (!consumeIdentifier(false, name))
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
	if (!consume(false, PROTOCOL_KEYWORD))
		return nullptr;

	if (!consumeIdentifier(false, name))
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

	if (!consumeIdentifier(false, name))
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

	if (!consumeIdentifier(true, name))
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

	if (consumeNumber(true, repeatFrom)) {
		readFrom = true;
	} else {
	    repeatFrom = 0;
	}

	// if there is a comma, we might try to consume a second number
	if (consume(true, COMMA)) {
	    commaSeperated = true;

	    // if there is no second number after a comma
	    if (!consumeNumber(true, repeatTo))
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

	if (!consumeIdentifier(false, name))
		return nullptr;

	// there is a value assigned to the field
	if (consume(true, ASSIGNMENT)) {
		isAssigned = true;

		if (!consumeNumber(false, valueAssigned))
			return nullptr;
	}

	if (!consume(false, SEMICOLON))
		return nullptr;

	return std::make_shared<Field>(type, name, isAssigned, valueAssigned);
}

std::shared_ptr<Type> Parser::parseType() {
	TokenType type;
	std::shared_ptr<Expression> length;

	if (!consumeType(true, type))
		return nullptr;

	if (!consume(false, OPEN_PARENT))
		return nullptr;

	if ((length = parseExpression()) == nullptr)
		return nullptr;

	if (!consume(false, CLOSE_PARENT))
		return nullptr;

	return std::make_shared<Type>(type, length);
}

std::shared_ptr<Expression> Parser::parseExpression() {
	std::shared_ptr<Operand> first;
	std::vector<std::pair<TokenType, std::shared_ptr<Operand>>> rest;

	unsigned int number;
	std::string str;
	TokenType type;

	if (consumeNumber(true, number))
		first = std::make_shared<Number>(number);
	else if (consumeIdentifier(true, str))
		first = std::make_shared<Identifier>(str);
	else {
		src.raiseError("Expected identifier or number before " +
		               strToWhite("'" + Scanner::tokenToString(token.type) + "'"), token);
		nextToken();

		return nullptr;
	}

	while (consumeOperator(true, type)) {
		if (consumeNumber(true, number)) {
			rest.push_back(std::make_pair(type, std::make_shared<Number>(number)));
		} else if (consumeIdentifier(true, str))
			rest.push_back(std::make_pair(type, std::make_shared<Identifier>(str)));
		else {
			src.raiseError("Expected identifier or number before " +
			               strToWhite("'" + Scanner::tokenToString(token.type) + "'"), token);
			nextToken();

			return nullptr;
		}
	}

	return std::make_shared<Expression>(first, rest);
}

bool Parser::consume(bool isPermissive, TokenType expected) {
	if (token.type == expected) {
		nextToken();

		return true;
	}

	// report an error
	if (!isPermissive) {
		src.raiseError("Expected " + strToWhite("'" + Scanner::tokenToString(expected) + "'") + " before " +
		               strToWhite("'" + Scanner::tokenToString(token.type) + "'"), token);

		nextToken();
	}

	return false;
}

bool Parser::consumeIdentifier(bool isPermissive, std::string &str) {
	if (token.type == IDENTIFIER) {
		str = token.stringValue;
		nextToken();
		return true;
	} else if (!isPermissive) {
		src.raiseError("Expected identifier before " +
		               strToWhite("'" + Scanner::tokenToString(token.type) + "'"), token);

		nextToken();

		return false;
	}
}

bool Parser::consumeNumber(bool isPermissive, unsigned int &number) {
	if (token.type == DEC_NUMBER || token.type == HEX_NUMBER) {
		number = token.intValue;
		nextToken();

		return true;
	}

	if (!isPermissive) {
		src.raiseError("Expected identifier before " +
		               strToWhite("'" + Scanner::tokenToString(token.type) + "'"), token);

		nextToken();
	}

	return false;
}

bool Parser::consumeType(bool isPermissive, enum TokenType &type) {
	if (token.type != INT_TYPE && token.type != UINT_TYPE && token.type != BYTES_TYPE &&
			token.type != BITS_TYPE && token.type != STRING_TYPE) {

		if (!isPermissive) {
			src.raiseError("Expected identifier before " +
			               strToWhite("'" + Scanner::tokenToString(token.type) + "'"), token);

			nextToken();
		}



		return false;
	}

	type = token.type;

	nextToken();

	return true;
}

bool Parser::consumeOperator(bool isPermissive, TokenType &type) {
	if (token.type != ADD_OPERATOR && token.type != MUL_OPERATOR && token.type != SUBTR_OPERATOR) {

		if (!isPermissive) {
			src.raiseError("Expected operator before " +
			               strToWhite("'" + Scanner::tokenToString(token.type) + "'"), token);

			nextToken();
		}

		return false;
	}

	type = token.type;

	nextToken();

	return true;
}
