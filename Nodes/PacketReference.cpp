#include "PacketReference.h"

std::shared_ptr<PacketsParser> PacketReference::parser = nullptr;

void PacketReference::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "PACKET REFERENCE name: " << Reference::name << std::endl;
}
