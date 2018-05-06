#ifndef TKOM_OPERATION_H
#define TKOM_OPERATION_H

#include "Node.h"

class Operation : public Node {
public:
	virtual int call() = 0;
	virtual void traverseParseTree(int level) = 0;
};
#endif //TKOM_OPERATION_H
