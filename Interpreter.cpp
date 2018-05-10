#include <unordered_set>
#include "Interpreter.h"
#include "Nodes/PacketReference.h"
#include "Colors.h"

bool Interpreter::fillPacketsMap() {
	std::unordered_set<std::string> packetsMap;
	std::unordered_map<uint64_t, std::unique_ptr<Packet>> pidMap;

	for (auto &p : prot->packets) {
		// names must be unique
		if (!packetsMap.insert(p->name).second) {
			std::cerr << "Packet of pid " << strToWhite("'" + std::to_string(p->pid) + "'") << " already defined!\n";
			return false;
		}

		// find packet's pid
		if (!p->setPid(assignedPid, pidOffset, pidLength))
			return false;

		if (!checkPacketFields(p))
			return false;

		// pids must be unique
		if (pidMap.find(p->pid) != pidMap.end()) {
			std::cerr << "Packet of pid " << strToWhite("'" + std::to_string(p->pid) + "'") << " already defined!\n";
			return false;
		}

		pidMap[p->pid] = std::move(p);
	}

	packetsParser = std::make_shared<PacketsParser>(fileName, std::move(pidMap), pidOffset, pidLength);

	PacketReference::parser = packetsParser;

	return true;
}

bool Interpreter::checkPacketFields(const std::unique_ptr<Packet> &p) {
	for (auto it = p->fields.begin(); it != p->fields.end(); it++) {

		// if first operand is dependent
		if ((*it)->type->length->first->getType() == IDENT) {
			Identifier *i = static_cast<Identifier*>((*it)->type->length->first.get());

			// look for a field
			bool found = false;
			for (auto it2 = p->fields.begin(); it2 != it; it2++) {
				if (i->str == (*it2)->name) {
					if ((*it2)->type->type != INT_TYPE && (*it2)->type->type != UINT_TYPE) {
						std::cerr << "Packet's: " << strToWhite("'" + p->name + "'") << " field depends on wrong type of field: " <<
						          strToWhite("'" + (*it2)->name + "'") << "\n";
						return false;
					}
					found = true;
				}
			}

			if (!found) {
				std::cerr << "Packet's " << strToWhite("'" + p->name + "'") << " field: " <<
				          strToWhite("'" + (*it)->name + "'") << " has unresolved dependencies" << "\n";
				return false;
			}
		}

		for (auto &op : (*it)->type->length->rest) {
			if (op.second->getType() != IDENT)
				continue;

			Identifier *i = static_cast<Identifier*>(op.second.get());

			// look for a field
			bool found = false;
			for (auto it2 = p->fields.begin(); it2 != it; it2++) {
				if (i->str == (*it2)->name) {
					found = true;
				}
			}

			if (!found) {
				std::cerr << "Packet's " << strToWhite("'" + p->name + "'") << " field: " <<
				          strToWhite("'" + (*it)->name + "'") << " has unresolved dependencies" << "\n";
				return false;
			}

		}
	}

	return true;
}

bool Interpreter::fillSequenceMap() {
	std::unordered_map<std::string, std::unique_ptr<Sequence>> sequenceMap;
	for (auto &s : prot->sequences) {
		if (sequenceMap.find(s->name) != sequenceMap.end()) {
			std::cerr << "Sequence of name " << strToWhite("'" + s->name + "'") << " already defined!\n";
			return false;
		}

		sequenceMap[s->name] = std::move(s);
	}

	SequenceReference::sequenceMap = std::move(sequenceMap);

	return true;
}
