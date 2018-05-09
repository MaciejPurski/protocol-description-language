#include "SequenceReference.h"

std::unordered_map<std::string, std::shared_ptr<Sequence>> SequenceReference::sequenceMap;

void SequenceReference::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "SEQUENCE REFERENCE name: " << Reference::name << std::endl;

}

bool SequenceReference::execute(std::deque<std::string> &callQueue, unsigned int depth,
									 unsigned int &positionPointer)
{
	return sequenceMap[Reference::name]->execute(callQueue, depth, positionPointer);
}
