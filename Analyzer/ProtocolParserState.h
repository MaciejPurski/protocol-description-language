#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_PROTOCOLPARSERSTATE_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_PROTOCOLPARSERSTATE_H

#include <deque>
#include <stack>
#include "PacketsScanner.h"
#include "../Utils.h"

class ProtocolParserState {
private:
	using CallQueue = std::deque<std::string>;
	using ParserState = std::pair<unsigned int, CallQueue>;

	PacketsScanner &scanner;
	unsigned int currentIndex;
	CallQueue callQueue;

	std::stack<ParserState> memoryStack;

public:
	ProtocolParserState(PacketsScanner &nscanner) : scanner(nscanner) {
		currentIndex = 0;
	}

	std::string getCurrentPacketName() {
		if (currentIndex >= scanner.getNPackets())
			throw std::runtime_error("No more available packets");

		return scanner.getPacket(currentIndex).name;
	}

	void showResult() {
		for (auto &s : callQueue)
			std::cout << s << std::endl;
	}

	void pushCurrentPacket(unsigned int depth) {
		std::string str;
		for (int i = 0; i < depth; i++)
			str += '\t';

		callQueue.push_back(strToYellow(str + "PACKET: ") + strToWhite(scanner.getPacket(currentIndex).toStr()));
		currentIndex++;
	}

	void pushSequence(std::string &name, unsigned int depth) {
		std::string str;
		for (int i = 0; i < depth; i++)
			str += '\t';

		callQueue.push_back("\n" + strToBlue(str + "SEQUENCE call: ") + strToWhite(name));
	}

	void saveCurrentState() {
		memoryStack.push(std::make_pair(currentIndex, callQueue));
	}

	void restoreState() {
		ParserState state = memoryStack.top();

		currentIndex = state.first;
		callQueue = state.second;
		memoryStack.pop();
	}

	void popState() {
		memoryStack.pop();
	}

	bool endOfBuffer() {
		return (currentIndex == scanner.getNPackets());
	}
};
#endif
