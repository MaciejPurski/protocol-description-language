#include <iostream>
#include "Packet.h"
#include "../Source.h"
#include "../Utils.h"

void Packet::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "PACKET name: " << name;

	std::cout << std::endl;

	for (const auto &f : fields)
		f->traverseParseTree(level + 1);

}

bool Packet::setPid(bool &assignedPid, unsigned int &pidOffset, unsigned int &pidLength) {
	unsigned int offset = 0;

	for (const auto &f : fields) {
		if (f->name == "pid") {
			if (!assignedPid) {
				assignedPid = true;
			} else if (offset != pidOffset) {
				std::cerr << "Pid offset of packet: " << strToWhite("'" + name + "'") << " differs from others" << "\n";
				return false;
			}

			if (!f->isAssigned) {
				std::cerr << "No value assigned for pid of packet " << strToWhite("'" + name + "'") << "\n";
				return false;
			}

			pid = f->assignedValue;
			// TODO: variable pid length
			pidLength = 1;
			pidOffset = offset;
			return true;
		}

		if (f->isDependent()) {
			std::cerr << "Pid of packet: " << strToWhite("'" + name + "'") << "is defined after dependent fields" << "\n";
			return false;
		}

		// TODO: get a non-dependent length of a field
		//offset += f->getLength();
	}

	std::cerr << "Packet " << strToWhite("'" + name + "'") << " does not have a pid field defined!\n";
	return false;
}

unsigned int Packet::evaluateFieldLength(std::unique_ptr<Field> field) {

}
