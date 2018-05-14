#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_EXPRESSION_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_EXPRESSION_H

#include "../Token.h"
#include "Node.h"
#include "../Analyzer/AnalyzerField.h"
#include "../Analyzer/AnalyzerPacket.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

enum OperandType {NUMBER, IDENT};

struct Operand: public Node {
	virtual void traverseParseTree(int level) = 0;
	virtual unsigned long getValue(std::vector<AnalyzerField> &fields) = 0;
	virtual OperandType getType() = 0;
};

struct Number : public Operand {
	unsigned int value;

	Number(unsigned int nValue) : value(nValue) { }

	void traverseParseTree(int level) {
		for (int i = 0; i < level; i++)
			std::cout << "-";

		std::cout << "NUMBER: " << value << std::endl;
	}

	unsigned long getValue(std::vector<AnalyzerField> &fields) {
		return value;
	}

	OperandType getType() {
		return NUMBER;
	}
};

struct Identifier : public Operand {
	std::string str;

	Identifier(std::string &nStr) : str(nStr) { }

	void traverseParseTree(int level) {
		for (int i = 0; i < level; i++)
			std::cout << "-";

		std::cout << "IDENTIFIER OPERAND: " << str << std::endl;
	}
	unsigned long getValue(std::vector<AnalyzerField> &fields) {
		for (auto &f : fields)
			if (f.name == str)
				return f.getUintVal();

		throw std::runtime_error("Unkown reference to field: " + str);
	}

	OperandType getType() {
		return IDENT;
	}
};

class Expression : public Node {
public:
	std::vector<std::unique_ptr<Operand>> operands;
	std::vector<TokenType> operators;

	Expression(std::vector<std::unique_ptr<Operand>> operands, std::vector<TokenType> operators) :
			operands(std::move(operands)), operators(std::move(operators)) {}

	unsigned long evaluate(std::vector<AnalyzerField> &fields);

	void traverseParseTree(int level);
};


#endif //PROTOCOL_DESCRIPTION_LANGUAGE_EXPRESSION_H
