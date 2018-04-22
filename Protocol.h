#ifndef TKOM_PROGRAM_H
#define TKOM_PROGRAM_H

#include <vector>
#include <memory>
#include <bits/shared_ptr.h>
#include "Packet.h"
#include "Sequence.h"
#include "Node.h"

class Protocol : public Node {
public:
	std::vector<std::shared_ptr<Packet>> packets;
	std::vector<std::shared_ptr<Sequence>> sequences;
	std::shared_ptr<Sequence> protocol;

	Protocol(std::vector<std::shared_ptr<Packet>> &p, std::vector<std::shared_ptr<Sequence>> &s, std::shared_ptr<Sequence> &prot) :
			packets(p), sequences(s), protocol(prot) {}

	void traverseParseTree(int level);
};


#endif //TKOM_PROGRAM_H
