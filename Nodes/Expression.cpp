#include <iostream>
#include "Expression.h"
#include "../Utils.h"


void Expression::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "Expression: ";

	std::cout << "OPERATORS: ";
	for (auto &op : operators)
		std::cout << tokenToString(op) << " ";

	std::cout << "OPERANDS: ";
	for (auto &opd : operands)
		opd->traverseParseTree(level + 1);

	std::cout << std::endl;
}

unsigned long Expression::evaluate(std::vector<AnalyzerField> &fields) {
	unsigned long value = operands.front()->getValue(fields);

	for (unsigned int i = 0; i < operators.size(); i++) {
		switch (operators[i]) {
			case MUL_OPERATOR:
				value *= operands[i + 1]->getValue(fields);
				break;
			case ADD_OPERATOR:
				value += operands[i + 1]->getValue(fields);
				break;
			case SUBTR_OPERATOR:
				value -= operands[i + 1]->getValue(fields);
				break;
			default:
				throw std::runtime_error("Unkown operator");
		}
	}

	return value;
}
