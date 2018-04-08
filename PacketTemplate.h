#ifndef TKOM_PACKETTEMPLATE_H
#define TKOM_PACKETTEMPLATE_H

#include <iostream>
#include <string>
#include <vector>
#include "Field.h"

class PacketTemplate {
	friend class Packet;
private:
	std::string identifier;
	int length;
	std::vector<Field> fields;

};


#endif
