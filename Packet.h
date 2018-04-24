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

	Packet(std::string &nname, std::vector<std::shared_ptr<Field>> &f) : name(nname), fields(f) { }
private:

};


#endif //TKOM_PACKET_H
