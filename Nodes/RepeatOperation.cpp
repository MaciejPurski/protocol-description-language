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
RepeatOperation::execute(std::deque<std::string> &callQueue, unsigned int depth, unsigned int &pointerPosition) {
	unsigned int counter = 0;
	bool success;
	// values to be restored in case of failure
	unsigned int oldPosition = pointerPosition;
	unsigned int queueSize = callQueue.size();

	do {
		success = block->execute(callQueue, depth, pointerPosition);

		if (success)
			counter++;

	} while (success);

	std::cout << "repeat operation performed: " << counter << "times\n";
	if (counter < repeatFrom || counter > repeatTo) {
		//restore position and queue size
		pointerPosition = oldPosition;
		callQueue.resize(queueSize);

		return 0;
	}

	return 1;
}