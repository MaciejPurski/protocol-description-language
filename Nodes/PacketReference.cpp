#include "PacketReference.h"

PacketsParser *PacketReference::parser = nullptr;

void PacketReference::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "PACKET REFERENCE name: " << Reference::name << std::endl;
}

bool PacketReference::execute(std::deque<std::string> &callQueue, unsigned int depth,
                                   unsigned int &pointerPosition) {
	std::cout << "try to get packet: " << Reference::name << std::endl;
	if (pointerPosition >= parser->getNPackets() || parser->getPacket(pointerPosition).name != Reference::name) {
		std::cout << "fail getting packet: " << Reference::name << std::endl;
		return 0;
	}

	pointerPosition++;
	std::string str;
	for (int i = 0; i < depth; i++)
		str += '-';

	callQueue.push_back(str + "packet: " + name);
	std::cout << "pushed " << str + "packet: " + name << std::endl;

	return 1;
}
