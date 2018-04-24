#include <iostream>
#include "Packet.h"

void Packet::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "PACKET name: " << name;

	std::cout << std::endl;

	for (auto f : fields)
		f->traverseParseTree(level + 1);

}
