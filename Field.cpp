#include <iostream>
#include "Field.h"

void Field::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "FIELD name: " << name;

	if (isAssigned)
		std::cout << "Assigned value: " << assignedValue;

	std::cout << std::endl;

	type->traverseParseTree(level + 1);
}
