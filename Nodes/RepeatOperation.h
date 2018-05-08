#ifndef TKOM_REPEATBLOCK_H
#define TKOM_REPEATBLOCK_H

#include "Operation.h"
#include "Block.h"

class RepeatOperation : public Operation {
public:
	unsigned int repeatFrom;
	unsigned int repeatTo;
	std::shared_ptr<Block> block;
	void traverseParseTree(int level);
	bool execute(std::deque<std::string> &callQueue, unsigned int depth,
	                  unsigned int &pointerPosition);

	RepeatOperation(unsigned int from, unsigned int to, std::shared_ptr<Block> &b) : repeatFrom(from),
	                                                                                 repeatTo(to),
	                                                                                 block(b) {}

};

#endif
