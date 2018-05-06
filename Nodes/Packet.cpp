#include <iostream>
#include "Packet.h"
#include "../Source.h"

void Packet::traverseParseTree(int level) {
	for (int i = 0; i < level; i++)
		std::cout << '-';

	std::cout << "PACKET name: " << name;

	std::cout << std::endl;

	for (auto f : fields)
		f->traverseParseTree(level + 1);

}

bool Packet::setPid(bool &assignedPid, unsigned int &pidOffset) {
	unsigned int offset = 0;

	for (auto f : fields) {
		if (f->name == "pid") {
			if (!assignedPid) {
				assignedPid = true;
				pidOffset = offset;
			} else if (offset != pidOffset) {
				std::cerr << "Pid offset of packet: " << Source::strToWhite("'" + name + "'") << " differs from others" << "\n";
				return false;
			}

			if (!f->isAssigned) {
				std::cerr << "No value assigned for pid of packet " << Source::strToWhite("'" + name + "'") << "\n";
				return false;
			}

			pid = f;
			return true;
		}

		if (f->isDependent()) {
			std::cerr << "Pid of packet: " << Source::strToWhite("'" + name + "'") << "is defined after dependent fields" << "\n";
			return false;
		}

		offset += evaluateFieldLength(f);
	}

	std::cerr << "Packet " << Source::strToWhite("'" + name + "'") << " does not have a pid field defined!\n";
	return false;
}

unsigned int Packet::evaluateFieldLength(std::shared_ptr<Field> field) {
	unsigned int result = 0;
	std::shared_ptr<Expression> expr = field->type->length;
	std::shared_ptr<Number> n;
	std::shared_ptr<Identifier> i;

	OperandType t = expr->first->getType();

	switch (t) {
		case NUMBER:
			n = std::static_pointer_cast<Number>(expr->first);
			result += n->value;
			break;
		case IDENT:
			i = std::static_pointer_cast<Identifier>(expr->first);

			// look for a dependent field
			for (auto f : fields) {
				// found
				if (f->name == i->str) {
					result += evaluateFieldLength(f);
				}
			}
			break;
	}

	for (auto op : expr->rest) {
		t = op.second->getType();
		unsigned int val;

		switch (t) {
			case NUMBER:
				n = std::static_pointer_cast<Number>(op.second);
				val = n->value;
				break;
			case IDENT:
				i = std::static_pointer_cast<Identifier>(op.second);
				for (auto f : fields) {
					// found
					if (f->name == i->str) {
						val = evaluateFieldLength(f);
					}
				}
				break;
		}

		switch (op.first) {
			case ADD_OPERATOR:
				result += val;
				break;
			case MUL_OPERATOR:
				result *= val;
				break;
			case SUBTR_OPERATOR:
				result -= val;
				break;
		}
	}

	return result;
}
