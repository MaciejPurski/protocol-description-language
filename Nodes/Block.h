#ifndef TKOM_BLOCK_H
#define TKOM_BLOCK_H

#include <memory>
#include <vector>
#include <bits/shared_ptr.h>
#include <iostream>
#include "Operation.h"
#include "Node.h"

class Block : public Node, Executable {
public:
	std::vector<std::shared_ptr<Operation>> operations;

	bool execute(std::deque<std::string> &callQueue, unsigned int depth,
	             unsigned int &pointerPosition);
	Block(std::vector<std::shared_ptr<Operation>> &o) : operations(o) { }

	void traverseParseTree(int level);
};

#endif //TKOM_BLOCK_H
