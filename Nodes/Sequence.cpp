#include "Sequence.h"
#include "../Utils.h"

void Sequence::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "SEQUENCE name: " << name;

	std::cout << std::endl;

	block->traverseParseTree(level + 1);
}

bool Sequence::execute(std::deque<std::string> &callDeque, unsigned int depth, unsigned int &currentPosition) {
	std::string str;
	// remember current position in order to restore it later
	unsigned int oldPosition = currentPosition;
	unsigned long oldSize = callDeque.size();

	for (int i = 0; i < depth; i++) {
		str += '\t';
	}

	callDeque.push_back("\n" + strToBlue(str + "SEQUENCE call: ") + strToWhite(name));

	// execution failed
	if (!block->execute(callDeque, depth + 1, currentPosition)) {
		callDeque.resize(oldSize);
		currentPosition = oldPosition;
		return false;
	}

	return true;
}
