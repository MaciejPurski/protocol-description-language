#ifndef TKOM_PROGRAM_H
#define TKOM_PROGRAM_H

#include <vector>
#include <memory>
#include <bits/unique_ptr.h>
#include "Packet.h"
#include "Sequence.h"
#include "Node.h"

class Protocol : public Node {
public:
	std::vector<std::unique_ptr<Packet>> packets;
	std::vector<std::unique_ptr<Sequence>> sequences;
	std::unique_ptr<Sequence> protocol;

	Protocol(std::vector<std::unique_ptr<Packet>> &p, std::vector<std::unique_ptr<Sequence>> &s, std::unique_ptr<Sequence> &prot) :
			packets(std::move(p)), sequences(std::move(s)), protocol(std::move(prot)) {}

	void traverseParseTree(int level);
};


#endif //TKOM_PROGRAM_H
