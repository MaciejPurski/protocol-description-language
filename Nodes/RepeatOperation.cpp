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

bool
RepeatOperation::execute(ProtocolParserState &state, unsigned int depth) {
	unsigned int counter = 0;

	// values to be restored in case of failure
	state.saveCurrentState();

	while (block->execute(state, depth))
			counter++;

	if (counter < repeatFrom || counter > repeatTo) {
		//restore position and queue size
		state.restoreState();

		return false;
	}
	state.popState();

	return true;
}