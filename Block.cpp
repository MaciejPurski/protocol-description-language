
#include "Block.h"

void Block::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "BLOCK\n";

	for (auto o : operations)
		o->traverseParseTree(level + 1);
}
