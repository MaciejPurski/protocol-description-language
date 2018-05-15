#ifndef TKOM_SEQUENCEREFERENCE_H
#define TKOM_SEQUENCEREFERENCE_H

#include <iostream>
#include <unordered_map>
#include "Operation.h"
#include "Reference.h"
#include "Sequence.h"

class SequenceReference : public Reference {
public:
	static std::unordered_map<std::string, std::unique_ptr<Sequence>> sequenceMap;

	bool execute(ProtocolParserState &state, unsigned int depth);
	SequenceReference() {}
	void traverseParseTree(int level);
};


#endif
