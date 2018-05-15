#ifndef TKOM_REPEATBLOCK_H
#define TKOM_REPEATBLOCK_H

#include "Operation.h"
#include "Block.h"

class RepeatOperation : public Operation {
public:
	unsigned int repeatFrom;
	unsigned int repeatTo;
	std::unique_ptr<Block> block;
	void traverseParseTree(int level);
	bool execute(ProtocolParserState &state, unsigned int depth);

	RepeatOperation(unsigned int from, unsigned int to, std::unique_ptr<Block> &b) : repeatFrom(from),
	                                                                                 repeatTo(to),
	                                                                                 block(std::move(b)) {}

};

#endif
