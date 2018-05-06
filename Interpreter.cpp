#include "Interpreter.h"


bool Interpreter::fillPacketsMap() {
	for (auto p : prot->packets) {
		if (!packetsMap.insert(std::make_pair(p->name, p)).second) {
			std::cerr << "Packet " << Source::strToWhite("'" + p->name + "'") << " already defined!\n";
			return false;
		}

		// find packet's pid
		if (!p->setPid(assignedPid, pidOffset))
			return false;

		if (!pidMap.insert(std::make_pair(p->pid->assignedValue, p)).second) {
			std::cerr << "Packet of pid " << Source::strToWhite("'" + std::to_string(p->pid->assignedValue) + "'") << " already defined!\n";
			return false;
		}

		if (!checkPacketFields(p))
			return false;
	}

	return true;
}

bool Interpreter::checkPacketFields(std::shared_ptr<Packet> p) {
	for (auto it = p->fields.begin(); it != p->fields.end(); it++) {

		// if first operand is dependent
		if ((*it)->type->length->first->getType() == IDENT) {
			std::shared_ptr<Identifier> i = std::static_pointer_cast<Identifier>((*it)->type->length->first);

			// look for a field
			bool found = false;
			for (auto it2 = p->fields.begin(); it2 != it; it2++) {
				if (i->str == (*it2)->name) {
					if ((*it2)->type->type != INT_TYPE && (*it2)->type->type != UINT_TYPE) {
						std::cerr << "Packet's: " << Source::strToWhite("'" + p->name + "'") << " field depends on wrong type of field: " <<
						          Source::strToWhite("'" + (*it2)->name + "'") << "\n";
						return false;
					}
					found = true;
				}
			}

			if (!found) {
				std::cerr << "Packet's " << Source::strToWhite("'" + p->name + "'") << " field: " <<
				          Source::strToWhite("'" + (*it)->name + "'") << " has unresolved dependencies" << "\n";
				return false;
			}
		}

		for (auto op : (*it)->type->length->rest) {
			if (op.second->getType() != IDENT)
				continue;

			std::shared_ptr<Identifier> i = std::static_pointer_cast<Identifier>(op.second);

			// look for a field
			bool found = false;
			for (auto it2 = p->fields.begin(); it2 != it; it2++) {
				if (i->str == (*it2)->name) {
					found = true;
				}
			}

			if (!found) {
				std::cerr << "Packet's " << Source::strToWhite("'" + p->name + "'") << " field: " <<
				          Source::strToWhite("'" + (*it)->name + "'") << " has unresolved dependencies" << "\n";
				return false;
			}

		}
	}

	return true;
}

bool Interpreter::fillSequenceMap() {
	for (auto s : prot->sequences) {
		if (!sequenceMap.insert(std::make_pair(s->name, s)).second) {
			std::cerr << "Sequence " << Source::strToWhite("'" + s->name + "'") << " already defined!\n";
			return false;
		}

	}

	return true;
}
