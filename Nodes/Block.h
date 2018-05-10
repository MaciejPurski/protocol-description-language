#ifndef TKOM_BLOCK_H
#define TKOM_BLOCK_H

#include <memory>
#include <vector>
#include <bits/unique_ptr.h>
#include <iostream>
#include "Operation.h"
#include "Node.h"

class Block : public Node, Executable {
public:
	std::vector<std::unique_ptr<Operation>> operations;

	bool execute(std::deque<std::string> &callQueue, unsigned int depth,
	             unsigned int &pointerPosition);
	Block(std::vector<std::unique_ptr<Operation>> &o) : operations(std::move(o)) { }

	void traverseParseTree(int level);
};

#endif //TKOM_BLOCK_H
