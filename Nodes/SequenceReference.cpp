#include "SequenceReference.h"

std::unordered_map<std::string, std::unique_ptr<Sequence>> SequenceReference::sequenceMap;

void SequenceReference::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "SEQUENCE REFERENCE name: " << Reference::name << std::endl;

}

bool SequenceReference::execute(ProtocolParserState &state, unsigned int depth)
{
	auto it = sequenceMap.find(Reference::name);
	if (it == sequenceMap.end()) {
		throw std::runtime_error("Undefined reference to sequence: " + Reference::name);
	}

	return it->second->execute(state, depth);
}
