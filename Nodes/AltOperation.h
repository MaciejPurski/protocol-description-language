#ifndef TKOM_ALTBLOCK_H
#define TKOM_ALTBLOCK_H

#include <vector>
#include <memory>
#include <bits/unique_ptr.h>
#include "Operation.h"
#include "Block.h"
#include "../Analyzer/ProtocolParserState.h"

class AltOperation : public Operation {
public:
	std::vector<std::unique_ptr<Block>> blocks;

	void traverseParseTree(int level);

	bool execute(ProtocolParserState &state, unsigned int depth);

	AltOperation(std::vector<std::unique_ptr<Block>> &b) : blocks(std::move(b)) { }
};
#endif
