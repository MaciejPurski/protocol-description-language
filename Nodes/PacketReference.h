#ifndef TKOM_PACKETREFERENCE_H
#define TKOM_PACKETREFERENCE_H


#include "Operation.h"
#include "Reference.h"
#include "../Analyzer/PacketsScanner.h"
#include <iostream>

class PacketReference : public Reference {
public:
	bool execute(ProtocolParserState &state, unsigned int depth);
	void traverseParseTree(int level);
	PacketReference() {}
};


#endif
