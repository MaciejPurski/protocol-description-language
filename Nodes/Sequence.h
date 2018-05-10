#ifndef TKOM_SEQUENCEBLOCK_H
#define TKOM_SEQUENCEBLOCK_H

#include <deque>
#include "Block.h"
#include "Node.h"

class Sequence : public Node {
public:
	bool execute(std::deque<std::string> &callDeque, unsigned int depth,
	             unsigned int &pointerPosition);
	std::string name;
	std::unique_ptr<Block> block;

	Sequence(std::string &n, std::unique_ptr<Block> &b) : name(n), block(std::move(b)) {}
	void traverseParseTree(int level);
};


#endif //TKOM_SEQUENCEBLOCK_H
