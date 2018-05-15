
#include "Block.h"

void Block::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "BLOCK\n";

	for (const auto &o : operations)
		o->traverseParseTree(level + 1);
}

bool Block::execute(ProtocolParserState &state, unsigned int depth) {
	state.saveCurrentState();

	for (const auto &op : operations)
		if (!op->execute(state, depth)) {
			state.restoreState();
			return false;
		}

		state.popState();

	return true;
}
