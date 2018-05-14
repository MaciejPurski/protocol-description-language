#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H


#include "Scanner.h"
#include "Nodes/AltOperation.h"
#include "Nodes/SequenceReference.h"
#include "Nodes/Packet.h"
#include "Nodes/Sequence.h"
#include "Nodes/Reference.h"
#include "Nodes/RepeatOperation.h"
#include "Nodes/Protocol.h"

class Parser {
private:
	Scanner &s;
	Source &src;
	Token token;

	void nextToken() {
		token = s.nextToken();
	}

	std::unique_ptr<Packet> parsePacket();

	std::unique_ptr<Sequence> parseSequence();

	std::unique_ptr<Sequence> parseProtocol();

	std::unique_ptr<Block> parseBlock();

	std::unique_ptr<Operation> parseOperation();

	std::unique_ptr<Reference> parseReference();

	std::unique_ptr<RepeatOperation> parseRepeatOperation();

	std::unique_ptr<AltOperation> parseAltOperation();

	std::unique_ptr<SequenceReference> parseSequenceReference();

	std::unique_ptr<RepeatOperation> parseSimpleRepeatOperation();

	std::unique_ptr<RepeatOperation> parseCompoundRepeatOperation();

	std::unique_ptr<Field> parseField();

	std::unique_ptr<Type> parseType();

	std::unique_ptr<Expression> parseExpression();


	bool consume(TokenType expected, bool isPermissive);

	bool consumeNumber(bool isPermissive, unsigned int *number);

	bool consumeIdentifier(std::string &str, bool isPermissive);

	bool consumeType(enum TokenType &type, bool isPermissive);

	bool consumeOperator(TokenType &type, bool isPermissive);

public:
	Parser(Scanner &ns, Source &nsrc) : s(ns), src(nsrc) {
		nextToken();
	}

	std::unique_ptr<Protocol>  parse();

	bool consumeNumber(unsigned int &number, bool isPermissive);

	std::unique_ptr<Operand> parseOperand();
};


#endif //TKOM_PARSER_H
