#ifndef TKOM_SEQUENCEBLOCK_H
#define TKOM_SEQUENCEBLOCK_H

#include "Block.h"
#include "Node.h"

class Sequence : public Node {
public:
	int execute();
	std::string name;
	std::shared_ptr<Block> block;

	Sequence(std::string &n, std::shared_ptr<Block> &b) : name(n), block(b) {}
	void traverseParseTree(int level);
};


#endif //TKOM_SEQUENCEBLOCK_H
