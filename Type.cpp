#include <iostream>
#include "Type.h"

void Type::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << "-";

	std::cout << "Type: " << type << " length: " << length->value << std::endl;
}


