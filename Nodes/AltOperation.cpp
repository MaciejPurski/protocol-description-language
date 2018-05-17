
#include "AltOperation.h"

void AltOperation::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "ALT OPERATION\n";

	for (const auto &b : blocks)
		b->traverseParseTree(level + 1);
}

bool AltOperation::execute(ProtocolParserState &state, unsigned int depth) {
	for (const auto &b : blocks) {
		if (b->execute(state, depth)) {
			return true;
		}
	}

	return false;
}
