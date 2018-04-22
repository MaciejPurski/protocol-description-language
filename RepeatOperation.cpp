#include <climits>
#include "RepeatOperation.h"

void RepeatOperation::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << "-";

	std::cout << "REPEAT OPERATION from: " << repeatFrom << " to: ";
	if (repeatTo == UINT_MAX)
		std::cout << "inf\n";
	else
		std::cout << repeatTo << std::endl;

	block->traverseParseTree(level + 1);
}
