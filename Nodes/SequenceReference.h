#ifndef TKOM_SEQUENCEREFERENCE_H
#define TKOM_SEQUENCEREFERENCE_H

#include <iostream>
#include "Operation.h"
#include "Reference.h"
#include "Sequence.h"

class SequenceReference : public Reference {
public:
	static std::shared_ptr<> sequences;

	int call() {

	}
	std::string name;
	SequenceReference() {}
	void traverseParseTree(int level);
};


#endif
