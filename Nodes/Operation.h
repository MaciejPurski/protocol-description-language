#ifndef TKOM_OPERATION_H
#define TKOM_OPERATION_H

#include <deque>
#include "Node.h"
#include "Executable.h"
#include <string>

class Operation : public Node, Executable {
public:
	virtual bool execute(std::deque<std::string> &callQueue, unsigned int depth,
	                          unsigned int &pointerPosition) = 0;
	virtual void traverseParseTree(int level) = 0;
};
#endif //TKOM_OPERATION_H
