#ifndef TKOM_SEQUENCEREFERENCE_H
#define TKOM_SEQUENCEREFERENCE_H

#include <iostream>
#include <unordered_map>
#include "Operation.h"
#include "Reference.h"
#include "Sequence.h"

class SequenceReference : public Reference {
public:
	static std::unordered_map<std::string, std::shared_ptr<Sequence>> sequenceMap;

	bool execute(std::deque<std::string> &callQueue, unsigned int depth,
	                  unsigned int &positionPointer);
	SequenceReference() {}
	void traverseParseTree(int level);
};


#endif
