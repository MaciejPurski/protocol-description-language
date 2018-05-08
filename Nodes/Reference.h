#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_REFERENCE_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_REFERENCE_H

#include <string>
#include "Operation.h"

class Reference : public Operation {
public:
	virtual bool execute(std::deque<std::string> &callQueue, unsigned int depth,
	                          unsigned int &positionPointer) = 0;
	virtual void traverseParseTree(int level) = 0;
	std::string name;
};
#endif //PROTOCOL_DESCRIPTION_LANGUAGE_REFERENCE_H
