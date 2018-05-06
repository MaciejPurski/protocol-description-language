#include <iostream>
#include "Expression.h"
#include "../Scanner.h"


void Expression::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::shared_ptr<Number> n;
	std::shared_ptr<Identifier> i;

	std::cout << "Expression: ";

	OperandType t = first->getType();
	switch (t) {
		case NUMBER:
			n = std::static_pointer_cast<Number>(first);
			std::cout << "number: " << n->value << " ";
			break;
		case IDENT:
			i = std::static_pointer_cast<Identifier>(first);
			std::cout << "identifier: " << i->str << " ";
			break;
	}

	for (auto op : rest) {
		std::cout << "operator: " << Scanner::tokenToString(op.first) << " ";

		t = op.second->getType();
		switch (t) {
			case NUMBER:
				n = std::static_pointer_cast<Number>(op.second);
				std::cout << "number: " << n->value << " ";
				break;
			case IDENT:
				i = std::static_pointer_cast<Identifier>(op.second);
				std::cout << "identifier: " << i->str << " ";
				break;
		}
	}

	std::cout << std::endl;
}
