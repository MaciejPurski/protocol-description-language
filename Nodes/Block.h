#ifndef TKOM_BLOCK_H
#define TKOM_BLOCK_H

#include <memory>
#include <vector>
#include <bits/unique_ptr.h>
#include <iostream>
#include "Operation.h"
#include "Node.h"
#include "../Analyzer/ProtocolParserState.h"

class Block : public Node, Executable {
public:
	std::vector<std::unique_ptr<Operation>> operations;

	bool execute(ProtocolParserState &state, unsigned int depth);

	Block(std::vector<std::unique_ptr<Operation>> &o) : operations(std::move(o)) { }

	void traverseParseTree(int level);
};

#endif //TKOM_BLOCK_H
