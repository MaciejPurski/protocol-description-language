#include "PacketReference.h"
#include "../Utils.h"

void PacketReference::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "PACKET REFERENCE name: " << Reference::name << std::endl;
}

bool PacketReference::execute(ProtocolParserState &state, unsigned int depth) {

	if (state.endOfBuffer() || state.getCurrentPacketName() != Reference::name) {
		return false;
	}
	state.pushCurrentPacket(depth);

	return true;
}
