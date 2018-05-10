#ifndef TKOM_PACKET_H
#define TKOM_PACKET_H

#include "Node.h"
#include "Field.h"
#include <string>
#include <vector>
#include <memory>

class Packet : public Node {
public:
	void traverseParseTree(int level);
	std::string name;
	std::vector<std::unique_ptr<Field>> fields;
	uint64_t pid;

	bool checkUniqueField();
	bool setPid(bool &assignedPid, unsigned int &pidOffset, unsigned int &pidLength);

	Packet(std::string &nname, std::vector<std::unique_ptr<Field>> f) : name(nname), fields(std::move(f)) { }

	unsigned int evaluateFieldLength(std::unique_ptr<Field> f);
private:

};


#endif //TKOM_PACKET_H
