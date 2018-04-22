#ifndef TKOM_SEQUENCEREFERENCE_H
#define TKOM_SEQUENCEREFERENCE_H

#include <iostream>
#include "Operation.h"

class SequenceReference : public Operation {
public:
	int call() {

	}
	std::string name;
	SequenceReference() {}
	void traverseParseTree(int level);
};


#endif
