#ifndef TKOM_PACKETREFERENCE_H
#define TKOM_PACKETREFERENCE_H


#include "Operation.h"
#include "Reference.h"
#include "../Analyzer/PacketsParser.h"
#include <iostream>

class PacketReference : public Reference {
public:
	static std::shared_ptr<PacketsParser> parser;

	bool execute(std::deque<std::string> &callQueue, unsigned int depth,
	                  unsigned int &pointerPosition);
	void traverseParseTree(int level);
	PacketReference() {}
};


#endif
