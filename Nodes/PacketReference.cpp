#include "PacketReference.h"
#include "../Colors.h"

std::shared_ptr<PacketsParser> PacketReference::parser = nullptr;

void PacketReference::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "PACKET REFERENCE name: " << Reference::name << std::endl;
}

bool PacketReference::execute(std::deque<std::string> &callQueue, unsigned int depth,
                                   unsigned int &pointerPosition) {

	if (pointerPosition >= parser->getNPackets() || parser->getPacket(pointerPosition).name != Reference::name) {
		return false;
	}

	std::string str;
	for (int i = 0; i < depth; i++)
		str += '\t';

	callQueue.push_back(strToYellow(str + "PACKET: ") + strToWhite(parser->getPacket(pointerPosition).toStr()));
	pointerPosition++;

	return true;
}
