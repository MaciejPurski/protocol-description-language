#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_EXPRESSION_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_EXPRESSION_H

#include "../Token.h"
#include "Node.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

enum OperandType {NUMBER, IDENT};

struct Operand {
	virtual OperandType getType() = 0;
};

struct Number : public Operand {
	int value;

	Number(int nValue) : value(nValue) { }

	OperandType  getType() {
		return NUMBER;
	}
};

struct Identifier : public Operand {
	std::string str;

	Identifier(std::string nStr) : str(nStr) { }

	OperandType  getType() {
		return IDENT;
	}
};

class Expression : public Node {
public:
	std::unique_ptr<Operand> first;

	std::vector<std::pair<TokenType, std::unique_ptr<Operand>>> rest;

	Expression(std::unique_ptr<Operand> &nfirst, std::vector<std::pair<TokenType, std::unique_ptr<Operand>>> &nargs) :
			first(std::move(nfirst)), rest(std::move(nargs)) {}

	void traverseParseTree(int level);
};


#endif //PROTOCOL_DESCRIPTION_LANGUAGE_EXPRESSION_H
