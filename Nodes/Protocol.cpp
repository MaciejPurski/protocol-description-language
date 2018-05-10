#include "Protocol.h"

void Protocol::traverseParseTree(int level) {
	std::cout << "tree root - protocol";
	std::cout << std::endl;

	for (const auto &p : packets)
		p->traverseParseTree(level + 1);

	for (const auto &s : sequences)
		s->traverseParseTree(level + 1);

	if (protocol != nullptr)
		protocol->traverseParseTree(level + 1);
}
