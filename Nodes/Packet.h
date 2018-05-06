#ifndef TKOM_PACKET_H
#define TKOM_PACKET_H


#include <string>
#include <memory>
#include <vector>
#include "Node.h"
#include "Field.h"

class Packet : public Node {
public:
	void traverseParseTree(int level);
	std::string name;
	std::vector<std::shared_ptr<Field>> fields;
	std::shared_ptr<Field> pid;

	bool checkUniqueField();
	bool setPid(bool &assignedPid, unsigned int &pidOffset);

	Packet(std::string &nname, std::vector<std::shared_ptr<Field>> &f) : name(nname), fields(f) { }

	unsigned int evaluateFieldLength(std::shared_ptr<Field> f);
private:

};


#endif //TKOM_PACKET_H
