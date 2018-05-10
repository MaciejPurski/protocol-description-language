#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_FIELD_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_FIELD_H


#include <string>
#include <memory>
#include "Node.h"
#include "Type.h"

class Field : public Node {
public:
	void traverseParseTree(int level);
	std::unique_ptr<Type> type;
	std::string name;
	bool isAssigned;
	int assignedValue;
	bool isDependent();

	Field(std::unique_ptr<Type> type, std::string &name, bool isAssigned, int assignedValue) :
	                                                                                                        name(name),
	                                                                                                        isAssigned(
			                                                                                                        isAssigned),
	                                                                                                        assignedValue(
			                                                                                                        assignedValue) {
		this->type = std::move(type);
	}
	unsigned int getLength();

};


#endif //PROTOCOL_DESCRIPTION_LANGUAGE_FIELD_H
