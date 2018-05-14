#include <memory>
#include <climits>
#include <cstdarg>
#include "Parser.h"
#include "Utils.h"
#include "Nodes/PacketReference.h"

std::unique_ptr<Protocol> Parser::parse() {
	std::vector<std::unique_ptr<Packet>> packets;
	std::vector<std::unique_ptr<Sequence>> sequences;
	std::unique_ptr<Sequence> protocol;

	std::unique_ptr<Packet> p;
	std::unique_ptr<Sequence> s;


	/* Protocol might consist of packets and sequences,
	 * therefore we try to parse them until it is possible
	 */
	while ((p = parsePacket()) != nullptr ||
			(s = parseSequence()) != nullptr) {
		if (p != nullptr)
			packets.emplace_back(std::move(p));

		if (s != nullptr)
			sequences.emplace_back(std::move(s));
	}

	if (src.getNErrors() > 0) {
		std::cout << "parsing failed\n";
		return nullptr;
	}

	if ((protocol = parseProtocol()) == nullptr) {
		return nullptr;
	}

	return std::make_unique<Protocol>(packets, sequences, protocol);
}

std::unique_ptr<Sequence> Parser::parseSequence() {
	std::string name;
	std::vector<std::unique_ptr<Operation>> operations;

	// sequence must begin with a "sequence" keyword
	if (!consume(true, SEQUENCE_KEYWORD))
		return nullptr;

	if (!consumeIdentifier(false, name))
		return nullptr;

	std::unique_ptr<Block> block = parseBlock();

	if (block == nullptr)
		throw std::runtime_error("Expected protocol definition");

	return std::make_unique<Sequence>(name, block);
}

std::unique_ptr<Block> Parser::parseBlock() {
	std::vector<std::unique_ptr<Operation>> operations;
	std::unique_ptr<Operation> o;

	if (!consume(true, OPEN_BRACK))
		return nullptr;

	while ((o = parseOperation()) != nullptr)
		operations.push_back(std::move(o));

	if (!consume(false, CLOSE_BRACK))
		return nullptr;


	return std::make_unique<Block>(operations);
}

std::unique_ptr<Sequence> Parser::parseProtocol() {
	std::string name;
	std::vector<std::unique_ptr<Operation>> operations;

	//TODO: common
	// sequence must begin with a "sequence" keyword
	if (!consume(true, PROTOCOL_KEYWORD))
		return nullptr;

	if (!consumeIdentifier(false, name))
		return nullptr;

	std::unique_ptr<Block> block = parseBlock();

	if (block == nullptr)
		return nullptr;

	return std::make_unique<Sequence>(name, block);
}

std::unique_ptr<Packet> Parser::parsePacket() {
    std::string name;
    std::vector<std::unique_ptr<Field>> fields;
    std::unique_ptr<Field> f;

    // packet must begin with a "packet" keyword
    if (!consume(true, PACKET_KEYWORD))
	    return nullptr;

	if (!consumeIdentifier(false, name))
		return nullptr;

	if (!consume(false, OPEN_BRACK))
		return nullptr;

	while ((f = parseField()) != nullptr)
		fields.push_back(std::move(f));

	if (!consume(false, CLOSE_BRACK))
		return nullptr;

    return std::make_unique<Packet>(name, std::move(fields));
}

std::unique_ptr<Operation> Parser::parseOperation() {
	std::unique_ptr<Operation> op;

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
std::unique_ptr<Reference> Parser::parseReference() {
	std::unique_ptr<Reference> ref;
	std::string name;

	if (!consumeIdentifier(true, name))
		return nullptr;

	// try to parse sequence reference, if it fails, treat it as a packet reference
	ref = parseSequenceReference();
	if (ref == nullptr)
		ref = std::make_unique<PacketReference>();

	// reference name is a common field of packet reference and sequence reference
	ref->name = name;
	if (!consume(false, SEMICOLON))
		return nullptr;

	return ref;
}


std::unique_ptr<RepeatOperation> Parser::parseRepeatOperation() {
	std::unique_ptr<RepeatOperation> op;

	if ((op = parseSimpleRepeatOperation()) != nullptr)
		return op;

	if ((op = parseCompoundRepeatOperation()) != nullptr)
		return op;

	return nullptr;
}

std::unique_ptr<AltOperation> Parser::parseAltOperation() {
	std::vector<std::unique_ptr<Block>> blocks;
	std::unique_ptr<Block> b;

	if (!consume(true, ALT_KEYWORD))
		return nullptr;

	if ((b = parseBlock()) == nullptr)
		throw std::runtime_error("Expected block");

	blocks.push_back(std::move(b));

	// need at least one "or" statement
	if (!consume(false, OR_KEYWORD))
		return nullptr;

	do  {
		if ((b = parseBlock()) == nullptr)
			throw std::runtime_error("Expected block");

		blocks.push_back(std::move(b));
	} while (consume(true, OR_KEYWORD));

	return std::make_unique<AltOperation>(blocks);
}

std::unique_ptr<SequenceReference> Parser::parseSequenceReference() {
	if (!consume(true, OPEN_PARENT))
		return nullptr;

	if (!consume(false, CLOSE_PARENT))
		return nullptr;

	return std::make_unique<SequenceReference>();
}

std::unique_ptr<RepeatOperation> Parser::parseSimpleRepeatOperation() {
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

	std::unique_ptr<Block> b;

	if ((b = parseBlock()) == nullptr)
		return nullptr;

	return std::make_unique<RepeatOperation>(repeatFrom, repeatTo, b);
}

std::unique_ptr<RepeatOperation> Parser::parseCompoundRepeatOperation() {
	unsigned int repeatFrom;
	unsigned int repeatTo;
	bool readFrom = false;

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

    std::unique_ptr<Block> b;

    if ((b = parseBlock()) == nullptr)
        throw std::runtime_error("Expected block");

    return std::make_unique<RepeatOperation>(repeatFrom, repeatTo, b);
}

std::unique_ptr<Field> Parser::parseField() {
	std::unique_ptr<Type> type;
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

	return std::make_unique<Field>(std::move(type), name, isAssigned, valueAssigned);
}

std::unique_ptr<Type> Parser::parseType() {
	TokenType type;
	std::unique_ptr<Expression> length;

	if (!consumeType(true, type))
		return nullptr;

	if (!consume(false, OPEN_PARENT))
		return nullptr;

	if ((length = parseExpression()) == nullptr)
		return nullptr;

	if (!consume(false, CLOSE_PARENT))
		return nullptr;

	return std::make_unique<Type>(type, length);
}

std::unique_ptr<Expression> Parser::parseExpression() {
	std::vector<std::unique_ptr<Operand>> operands;
	std::vector<TokenType> operators;
	std::unique_ptr<Operand> op;
	TokenType t;


	if ((op = parseOperand()) == nullptr)
		return nullptr;

	operands.push_back(std::move(op));

	while (consumeOperator(true, t)) {
		operators.push_back(t);

		if ((op = parseOperand()) == nullptr)
			throw std::runtime_error("Expected operand");

		operands.push_back(std::move(op));
	}

	return std::make_unique<Expression>(std::move(operands), operators);
}

std::unique_ptr<Operand> Parser::parseOperand() {
	std::string str;
	unsigned int value;

	if (consumeNumber(true, value))
		return std::make_unique<Number>(value);

	if (consumeIdentifier(true, str))
		return std::make_unique<Identifier>(str);

	return nullptr;
}

bool Parser::consume(bool isPermissive, TokenType expected) {
	if (token.type == expected) {
		nextToken();

		return true;
	}

	// report an error
	if (!isPermissive) {
		src.raiseError("Expected " + strToWhite("'" + tokenToString(expected) + "'") + " before " +
		               strToWhite("'" + tokenToString(token.type) + "'"), token);

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
		               strToWhite("'" + tokenToString(token.type) + "'"), token);

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
		               strToWhite("'" + tokenToString(token.type) + "'"), token);

		nextToken();
	}

	return false;
}

bool Parser::consumeType(bool isPermissive, enum TokenType &type) {
	if (token.type != INT_TYPE && token.type != UINT_TYPE && token.type != BYTES_TYPE &&
			token.type != BITS_TYPE && token.type != STRING_TYPE) {

		if (!isPermissive) {
			src.raiseError("Expected identifier before " +
			               strToWhite("'" + tokenToString(token.type) + "'"), token);

			nextToken();
		}



		return false;
	}

	type = token.type;

	nextToken();

	return true;
}

//parse operand
bool Parser::consumeOperator(bool isPermissive, TokenType &type) {
	if (token.type != ADD_OPERATOR && token.type != MUL_OPERATOR && token.type != SUBTR_OPERATOR) {

		if (!isPermissive) {
			src.raiseError("Expected operator before " +
			               strToWhite("'" + tokenToString(token.type) + "'"), token);

			nextToken();
		}

		return false;
	}

	type = token.type;

	nextToken();

	return true;
}
