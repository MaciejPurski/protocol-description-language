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
	std::cout << "call sequence reference: " << Reference::name << std::endl;
	return sequenceMap[Reference::name]->execute(callQueue, depth, positionPointer);
}
