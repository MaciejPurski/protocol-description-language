
#include "AltOperation.h"

void AltOperation::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "ALT OPERATION\n";

	for (auto b : blocks)
		b->traverseParseTree(level + 1);
}
