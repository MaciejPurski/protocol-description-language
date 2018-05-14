#include <iostream>
#include "Field.h"

void Field::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "FIELD name: " << name;

	if (isAssigned)
		std::cout << " Assigned value: " << assignedValue;

	std::cout << std::endl;

	type->traverseParseTree(level + 1);
}

bool Field::isDependent() {
	for (auto &op : type->length->operands) {
		if (op->getType() == IDENT) {
			return true;
		}
	}

	return false;
}

unsigned int Field::getLength() {

	return 0;
}
