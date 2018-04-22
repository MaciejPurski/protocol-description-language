#ifndef TKOM_BLOCK_H
#define TKOM_BLOCK_H

#include <memory>
#include <vector>
#include <bits/shared_ptr.h>
#include <iostream>
#include "Operation.h"
#include "Node.h"

class Block : public Node {
public:
	std::vector<std::shared_ptr<Operation>> operations;

	Block(std::vector<std::shared_ptr<Operation>> &o) : operations(o) { }

	void traverseParseTree(int level);
};

#endif //TKOM_BLOCK_H
