
#include "AltOperation.h"

void AltOperation::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "ALT OPERATION\n";

	for (const auto &b : blocks)
		b->traverseParseTree(level + 1);
}

bool AltOperation::execute(std::deque<std::string> &callQueue, unsigned int depth,
                           unsigned int &pointerPosition) {

	for (const auto &b : blocks) {
		if (b->execute(callQueue, depth, pointerPosition))
			return true;
	}

	return false;
}
