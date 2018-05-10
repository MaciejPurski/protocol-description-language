#ifndef PROTOCOL_DESCRIPTION_LANGUAGE_TYPE_H
#define PROTOCOL_DESCRIPTION_LANGUAGE_TYPE_H


#include <memory>
#include "Node.h"
#include "../Token.h"
#include "Expression.h"

class Type : public Node {
public:
	void traverseParseTree(int level);
	TokenType type;
	std::unique_ptr<Expression> length;

	Type(TokenType type, std::unique_ptr<Expression> &length) : type(type), length(std::move(length)) {}


};


#endif //PROTOCOL_DESCRIPTION_LANGUAGE_TYPE_H
