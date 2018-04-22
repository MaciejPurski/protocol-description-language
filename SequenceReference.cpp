//
// Created by maciej on 22.04.18.
//

#include "SequenceReference.h"

void SequenceReference::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "SEQUENCE REFERENCE name: " << name << std::endl;

}
