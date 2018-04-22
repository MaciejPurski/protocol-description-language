#include "PacketReference.h"

void PacketReference::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "PACKET REFERENCE name: " << name << std::endl;
}
