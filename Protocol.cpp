#include "Protocol.h"

void Protocol::traverseParseTree(int level) {
	std::cout << "tree root - protocol";
	std::cout << std::endl;

	for (auto p : packets)
		p->traverseParseTree(level + 1);

	for (auto s : sequences)
		s->traverseParseTree(level + 1);

		protocol->traverseParseTree(level + 1);
}
