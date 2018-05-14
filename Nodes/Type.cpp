#include <iostream>
#include "Type.h"
#include "../Scanner.h"

void Type::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << "-";

	std::cout << "Type: " << tokenToString(type) << std::endl;

	length->traverseParseTree(level + 1);
}


