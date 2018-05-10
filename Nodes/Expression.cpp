#include <iostream>
#include "Expression.h"
#include "../Scanner.h"


void Expression::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	Number *n;
	Identifier *i;

	std::cout << "Expression: ";

	OperandType t = first->getType();
	switch (t) {
		case NUMBER:
			n = static_cast<Number*>(first.get());
			std::cout << "number: " << n->value << " ";
			break;
		case IDENT:
			i = static_cast<Identifier*>(first.get());
			std::cout << "identifier: " << i->str << " ";
			break;
	}

	for (const auto &op : rest) {
		std::cout << "operator: " << Scanner::tokenToString(op.first) << " ";

		t = op.second->getType();
		switch (t) {
			case NUMBER:
				n = static_cast<Number*>(op.second.get());
				std::cout << "number: " << n->value << " ";
				break;
			case IDENT:
				i = static_cast<Identifier*>(op.second.get());
				std::cout << "identifier: " << i->str << " ";
				break;
		}
	}

	std::cout << std::endl;
}
