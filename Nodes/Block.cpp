
#include "Block.h"

void Block::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "BLOCK\n";

	for (auto o : operations)
		o->traverseParseTree(level + 1);
}

bool Block::execute(std::deque<std::string> &callQueue, unsigned int depth, unsigned int &pointerPosition) {
	for (auto &op : operations)
		if (!op->execute(callQueue, depth, pointerPosition))
			return false;

	return true;
}
