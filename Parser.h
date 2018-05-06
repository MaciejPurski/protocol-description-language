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

	std::shared_ptr<Packet> parsePacket();

	std::shared_ptr<Sequence> parseSequence();

	std::shared_ptr<Sequence> parseProtocol();

	std::shared_ptr<Block> parseBlock();

	std::shared_ptr<Operation> parseOperation();

	std::shared_ptr<Reference> parseReference();

	std::shared_ptr<RepeatOperation> parseRepeatOperation();

	std::shared_ptr<AltOperation> parseAltOperation();

	std::shared_ptr<SequenceReference> parseSequenceReference();

	std::shared_ptr<RepeatOperation> parseSimpleRepeatOperation();

	std::shared_ptr<RepeatOperation> parseCompoundRepeatOperation();

	std::shared_ptr<Field> parseField();

	std::shared_ptr<Type> parseType();

	std::shared_ptr<Expression> parseExpression();


	bool consume(bool isPermissive, TokenType expected);

	bool consumeNumber(bool isPermissive, unsigned int *number);

	bool consumeIdentifier(bool isPermissive, std::string &str);

	bool consumeType(bool isPermissive, TokenType &type);

	bool consumeOperator(bool isPermissive, TokenType &type);

public:
	Parser(Scanner &ns, Source &nsrc) : s(ns), src(nsrc) {
		nextToken();
	}

	std::shared_ptr<Protocol>  parse();

	bool consumeNumber(bool isPermissive, unsigned int &number);
};


#endif //TKOM_PARSER_H
