#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_EXECUTABLE_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_EXECUTABLE_H

#include <deque>
#include <string>
#include "../Analyzer/ProtocolParserState.h"

class Executable {
	virtual bool execute(ProtocolParserState &state, unsigned int depth) = 0;
};
#endif
