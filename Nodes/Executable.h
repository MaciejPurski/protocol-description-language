#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_EXECUTABLE_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_EXECUTABLE_H

#include <deque>
#include <string>

class Executable {
	virtual bool execute(std::deque<std::string> &callQueue, unsigned int depth,
						 unsigned int &pointerPosition) = 0;
};
#endif
