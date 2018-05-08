#include "SequenceReference.h"

void SequenceReference::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "SEQUENCE REFERENCE name: " << Reference::name << std::endl;

}
