#include <unordered_set>
#include "Interpreter.h"
#include "Nodes/PacketReference.h"
#include "Utils.h"

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
