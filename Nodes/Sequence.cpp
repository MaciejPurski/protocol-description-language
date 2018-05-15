#include "Sequence.h"
#include "../Utils.h"
#include "../Analyzer/ProtocolParserState.h"

void Sequence::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "SEQUENCE name: " << name;

	std::cout << std::endl;

	block->traverseParseTree(level + 1);
}

bool Sequence::execute(ProtocolParserState &state, unsigned int depth) {
	std::string str;
	// remember current sequence
	state.pushSequence(name, depth);

	return block->execute(state, depth + 1);
}
