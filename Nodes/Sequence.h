#ifndef TKOM_SEQUENCEBLOCK_H
#define TKOM_SEQUENCEBLOCK_H

#include <deque>
#include "Block.h"
#include "Node.h"
#include "../Analyzer/ProtocolParserState.h"

class Sequence : public Node {
public:
	bool execute(ProtocolParserState &state, unsigned int depth);
	std::string name;
	std::unique_ptr<Block> block;

	Sequence(std::string &n, std::unique_ptr<Block> &b) : name(n), block(std::move(b)) {}
	void traverseParseTree(int level);
};


#endif //TKOM_SEQUENCEBLOCK_H
