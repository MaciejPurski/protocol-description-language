#include "Sequence.h"

void Sequence::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "SEQUENCE name: " << name;

	std::cout << std::endl;

	block->traverseParseTree(level + 1);
}
