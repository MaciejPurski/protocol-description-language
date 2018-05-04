#ifndef TKOM_ALTBLOCK_H
#define TKOM_ALTBLOCK_H

#include <vector>
#include <memory>
#include <bits/shared_ptr.h>
#include "Operation.h"
#include "Block.h"

class AltOperation : public Operation {
public:
	std::vector<std::shared_ptr<Block>> blocks;

	void traverseParseTree(int level);

	int call() {

	}

	AltOperation(std::vector<std::shared_ptr<Block>> &b) : blocks(b) { }
};
#endif