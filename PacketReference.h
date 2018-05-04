#ifndef TKOM_PACKETREFERENCE_H
#define TKOM_PACKETREFERENCE_H


#include "Operation.h"
#include "Reference.h"
#include <iostream>

class PacketReference : public Reference {
public:
	int call() {

	}
	std::string name;
	void traverseParseTree(int level);
	PacketReference() {}
};


#endif
