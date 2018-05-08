#include "Sequence.h"

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

	for (int i = 0; i < depth; i++) {
		str += '-';
	}

	std::cout << "entered: " << name << std::endl;

	callDeque.push_back(str + "sequence: " + name);

	// execution failed
	if (!block->execute(callDeque, depth + 1, currentPosition)) {
		std::cout << "pop_back()\n";
		callDeque.pop_back();
		currentPosition = oldPosition;
		return false;
	}

	return true;
}
