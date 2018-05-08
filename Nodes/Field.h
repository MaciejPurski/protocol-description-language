#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_FIELD_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_FIELD_H


#include <string>
#include <memory>
#include "Node.h"
#include "Type.h"

class Field : public Node {
public:
	void traverseParseTree(int level);
	std::shared_ptr<Type> type;
	std::string name;
	bool isAssigned;
	int assignedValue;
	bool isDependent();

	Field(std::shared_ptr<Type> &type, std::string &name, bool isAssigned, int assignedValue) : type(type),
	                                                                                                        name(name),
	                                                                                                        isAssigned(
			                                                                                                        isAssigned),
	                                                                                                        assignedValue(
			                                                                                                        assignedValue) {}
	unsigned int getLength();

};


#endif //PROTOCOL_DESCRIPTION_LANGUAGE_FIELD_H
